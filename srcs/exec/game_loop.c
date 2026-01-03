/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:50:51 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/13 19:07:32 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	game_action(t_data *data)
{
	movement_handler(data);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	clear_layer(data->ray_layer, WIN_HEIGHT * WIN_WIDTH);
	cast_rays(data);
	project_walls(data);
	create_comp(data);
}

static int	game_loop(void *param)
{
	t_data					*data;
	static struct timeval	last_frame_time;
	static int				first_frame = 1;
	struct timeval			current_time;
	double					delta;

	data = (t_data *)param;
	if (!data || !data->ray_layer || !data->map_layer)
		return (1);
	gettimeofday(&current_time, NULL);
	if (first_frame)
	{
		last_frame_time = current_time;
		first_frame = 0;
	}
	delta = (current_time.tv_sec - last_frame_time.tv_sec)
		+ (current_time.tv_usec - last_frame_time.tv_usec) / 1000000.0;
	if (delta >= 1.0 / FPS)
	{
		game_action(data);
		last_frame_time = current_time;
	}
	return (0);
}

int	mlx_main_loop(t_data *data)
{
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, handle_keyrelease,
		data);
	mlx_hook(data->win_ptr, 17, 0, on_destroy, data);
	mlx_loop_hook(data->mlx_ptr, &game_loop, data);
	mlx_loop(data->mlx_ptr);
	on_destroy(data);
	return (0);
}
