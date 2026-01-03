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

#include <cub3d_bonus.h>

int	init_mlx(t_data *data)
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
		ft_fprintf(2, "Error\nNo start position for player\n");
		on_destroy(data);
		exit(EXIT_FAILURE);
	}
	find_coins(data, mapdata);
	if (data->gamestate->c_count == 0)
		data->gamestate->c_count = -1;
	if (find_start_rot_pos(data) == 1)
	{
		ft_fprintf(2, "Error\nNo start position for player\n");
		on_destroy(data);
		exit(EXIT_FAILURE);
	}
	if (player->x_pos < 0 || player->x_pos < 0)
	{
		ft_fprintf(2, "Error\nNo start position for player\n");
		on_destroy(data);
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	initialize_door_arrays(t_data *data, int height)
{
	data->mapdata->door_states = ft_calloc(height, sizeof(int *));
	data->mapdata->door_timers = ft_calloc(height, sizeof(double *));
}

void	init_door_row(t_data *data, int i, int row_width)
{
	int	j;

	j = 0;
	data->mapdata->door_states[i] = ft_calloc(row_width, sizeof(int));
	data->mapdata->door_timers[i] = ft_calloc(row_width, sizeof(double));
	while (j < row_width)
	{
		if (data->mapdata->map[i][j] == 'D')
			data->mapdata->door_states[i][j] = CLOSED;
		else
			data->mapdata->door_states[i][j] = -1;
		data->mapdata->door_timers[i][j] = 0.0f;
		j++;
	}
}

void	initialize_door_data(t_data *data)
{
	int	i;
	int	height;
	int	row_width;

	i = 0;
	height = data->mapdata->height;
	initialize_door_arrays(data, height);
	while (i < height)
	{
		if (!data->mapdata->map[i])
			continue ;
		row_width = ft_strlen(data->mapdata->map[i]);
		init_door_row(data, i, row_width);
		i++;
	}
	data->mapdata->door_active = false;
}
