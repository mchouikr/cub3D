/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:53:14 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 15:33:55 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	find_coins(t_data *data, t_mapdata *mapdata)
{
	int	x;
	int	y;

	y = 0;
	while (mapdata->map[y])
	{
		x = 0;
		while (mapdata->map[y][x])
		{
			if (mapdata->map[y][x] == 'C')
			{
				data->gamestate->c_count++;
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	initialize_input_data(t_data *data)
{
	data->input->w_pressed = 0;
	data->input->a_pressed = 0;
	data->input->s_pressed = 0;
	data->input->d_pressed = 0;
	data->input->left_pressed = 0;
	data->input->right_pressed = 0;
	data->input->space_pressed = 0;
}

static int	init_map_data(t_data *data, char **av)
{
	data->mapdata->map = return_map(av, data->mapdata);
	if (!data->mapdata->map)
	{
		ft_printf("Error\nFailed to return (map\n");
		on_destroy(data);
		return (EXIT_FAILURE);
	}
	data->mapdata->height = ft_tablen(data->mapdata->map);
	return (SUCCESS);
}

static void	calculate_map_width(t_data *data)
{
	int	max_width;
	int	row_len;
	int	i;

	max_width = 0;
	i = 0;
	while (i < data->mapdata->height)
	{
		row_len = ft_strlen(data->mapdata->map[i]);
		if (row_len > max_width)
			max_width = row_len;
		i++;
	}
	data->mapdata->width = max_width;
}

int	game_init(t_data *data, char **av)
{
	if (init_mlx(data) != 0 || load_textures(data, data->mapdata) != 0)
		return (FAILURE);
	if (init_map_data(data, av) != SUCCESS)
		return (FAILURE);
	calculate_map_width(data);
	initialize_input_data(data);
	init_player_pos(data, data->mapdata, data->player);
	initialize_door_data(data);
	data->sprite->num_sprites = data->gamestate->c_count;
	data->sprite->order = ft_calloc(data->sprite->num_sprites, sizeof(int));
	data->sprite->distance = ft_calloc(data->sprite->num_sprites,
			sizeof(double));
	return (SUCCESS);
}
