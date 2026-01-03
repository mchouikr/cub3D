/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:11:41 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 00:07:06 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static int	init_rays(t_data *data)
{
	int	i;

	i = 0;
	data->rays = ft_calloc(NUM_RAYS, sizeof(t_ray));
	if (!data->rays)
		return (1);
	return (0);
	while (i < NUM_RAYS)
	{
		data->rays[i].angle = 0;
		data->rays[i].distance = 0;
		data->rays[i].wall_hit_x = 0;
		data->rays[i].wall_hit_y = 0;
		data->rays[i].hit_vertical = 0;
		i++;
	}
}

static t_data	*init_data_structures(void)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->mapdata = ft_calloc(1, sizeof(t_mapdata));
	data->player = (t_player *)ft_calloc(1, sizeof(t_player));
	data->input = ft_calloc(1, sizeof(t_input));
	data->camera = ft_calloc(1, sizeof(t_camera));
	if (!data->mapdata || !data->player || !data->input || !data->camera)
	{
		on_destroy(data);
		return (NULL);
	}
	return (data);
}

static bool	init_game_structures(t_data *data)
{
	data->sprite = ft_calloc(1, sizeof(t_sprite));
	if (!data->sprite)
		return (false);
	data->gamestate = ft_calloc(1, sizeof(t_gamestate));
	if (!data->gamestate)
		return (false);
	data->sprite->zbuffer = ft_calloc(NUM_RAYS, sizeof(double));
	if (!data->sprite->zbuffer)
		return (false);
	return (true);
}

static t_data	*main_init(void)
{
	t_data	*data;

	data = init_data_structures();
	if (!data || !init_game_structures(data))
	{
		on_destroy(data);
		return (NULL);
	}
	if (init_rays(data) == 1)
	{
		on_destroy(data);
		return (NULL);
	}
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		data = main_init();
		if (data == NULL)
			return (on_destroy(data), ft_fprintf(2, DATA_INIT_FAIL), FAILURE);
		if (FOV < 50 || FOV > 120)
			return (on_destroy(data), ft_fprintf(2, WRONG_FOV), FAILURE);
		if (check_map_validity(av, data->mapdata) == FAILURE)
			return (on_destroy(data), FAILURE);
		if (game_init(data, av) == FAILURE)
			return (on_destroy(data), FAILURE);
		if (init_layers(data) == FAILURE)
			return (on_destroy(data), FAILURE);
		mlx_main_loop(data);
		return (SUCCESS);
	}
	ft_fprintf(2, "Error\n");
	ft_fprintf(1, "Usage: ./cub3d <path_to_map>\n");
	return (FAILURE);
}
