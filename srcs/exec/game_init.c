/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:03:18 by edelplan          #+#    #+#             */
/*   Updated: 2025/01/22 18:49:51 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		ft_fprintf(2, MLX_INIT_FAIL);
		on_destroy(data);
		exit(FAILURE);
	}
	if ((WIN_WIDTH >= 640 && WIN_WIDTH <= 1920) || (WIN_WIDTH >= 480
			&& WIN_WIDTH <= 1080))
		data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
				"cub3D");
	else
	{
		ft_fprintf(2, WRONG_RESOLUTION);
		on_destroy(data);
		exit(FAILURE);
	}
	if (data->win_ptr == NULL)
	{
		ft_fprintf(2, WIN_CREATE_FAIL);
		on_destroy(data);
		exit(FAILURE);
	}
	return (0);
}

int	init_player_pos(t_data *data, t_mapdata *mapdata, t_player *player)
{
	if (find_start_pos(data, mapdata) == 1)
	{
		ft_fprintf(2, NO_START_POSITION);
		on_destroy(data);
		exit(EXIT_FAILURE);
	}
	if (find_start_rot_pos(data) == 1)
	{
		ft_fprintf(2, NO_START_POSITION);
		on_destroy(data);
		exit(EXIT_FAILURE);
	}
	if (player->x_pos < 0 || player->x_pos < 0)
	{
		ft_fprintf(2, NO_START_POSITION);
		on_destroy(data);
		exit(EXIT_FAILURE);
	}
	return (SUCCESS);
}

int	game_init(t_data *data, char **av)
{
	if (init_mlx(data) != 0)
	{
		ft_fprintf(2, MLX_INIT_FAIL);
		return (FAILURE);
	}
	if (load_textures(data, data->mapdata) != 0)
		return (FAILURE);
	data->mapdata->map = return_map(av, data->mapdata);
	if (!data->mapdata->map)
	{
		ft_fprintf(2, RETURN_MAP_FAIL);
		return (FAILURE);
	}
	if (init_player_pos(data, data->mapdata, data->player) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
