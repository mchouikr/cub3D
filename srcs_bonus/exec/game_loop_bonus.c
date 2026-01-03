/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:50:51 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 15:37:15 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	game_action(t_data *data, double delta)
{
	movement_handler(data);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	clear_layer(data->ray_layer, WIN_HEIGHT * WIN_WIDTH);
	clear_layer(data->wall_layer, WIN_HEIGHT * WIN_WIDTH);
	clear_layer(data->sprite_layer, WIN_HEIGHT * WIN_WIDTH);
	update_door_animation(data, delta);
	cast_rays(data);
	project_walls(data);
	draw_sprites(data);
	draw_ray_hit(data);
	create_comp(data);
	if (data->gamestate->c_count == 0)
	{
		printf("You won\n");
		on_destroy(data);
		exit(0);
	}
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
		game_action(data, delta);
		last_frame_time = current_time;
	}
	return (0);
}

int	mlx_main_loop(t_data *data)
{
	if (!data)
	{
		printf("Invalid data pointer\n");
		return (1);
	}
	if (load_sprite_buffer(data))
	{
		printf("Failed to load sprite buffer\n");
		on_destroy(data);
		exit (1);
	}
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, handle_keyrelease,
		data);
	mlx_hook(data->win_ptr, 17, 0, on_destroy, data);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_loop_hook(data->mlx_ptr, &game_loop, data);
	mlx_loop(data->mlx_ptr);
	on_destroy(data);
	return (0);
}

// ==============DEBUG====================================================
// mlx_put_image_to_window(data.mlx_ptr, data.win_ptr,
//     data.textures[0], 350, 50);
// mlx_put_image_to_window(data.mlx_ptr, data.win_ptr,
//     data.textures[1], 500, 50);
// mlx_put_image_to_window(data.mlx_ptr, data.win_ptr,
//     data.textures[2], 350, 250);
// mlx_put_image_to_window(data.mlx_ptr, data.win_ptr,
//     data.textures[3], 500, 250);

// // Labels for textures
// mlx_string_put(data.mlx_ptr, data.win_ptr, 350, 30, 0xFFFFFF, "NO");
// mlx_string_put(data.mlx_ptr, data.win_ptr, 500, 30, 0xFFFFFF, "SO");
// mlx_string_put(data.mlx_ptr, data.win_ptr, 350, 230, 0xFFFFFF, "WE");
// mlx_string_put(data.mlx_ptr, data.win_ptr, 500, 230, 0xFFFFFF, "EA");
// mlx_string_put(data.mlx_ptr, data.win_ptr, 50, 250, 0xFFFFFF,
// "================DEBUG==================");
// mlx_string_put(data.mlx_ptr, data.win_ptr, 50, 275, 0xFFFFFF,
// "ESC TO EXIT !!!");
// mlx_string_put(data.mlx_ptr, data.win_ptr, 50, 300, 0xFFFFFF,
// "USE WASD TO MOVE");
// mlx_string_put(data.mlx_ptr, data.win_ptr, 50, 325, 0xFFFFFF,
// "USE ARROWS TO ROTATE");
// mlx_string_put(data.mlx_ptr, data.win_ptr, 50, 350, 0xFFFFFF,
// "=======================================");

// ==============DEBUG====================================================

// draw_ray_hit_static(&data, data.mapdata, 0, 0);