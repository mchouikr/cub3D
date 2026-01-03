/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:38:26 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 00:31:06 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	free_texture_resources(t_data *data)
{
	if (!data || !data->mlx_ptr)
		return ;
	free_texture_images(data);
	free_texture_buffers(data);
}

static void	free_door_arrays(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->mapdata->height)
	{
		if (data->mapdata->door_states)
			free(data->mapdata->door_states[i]);
		if (data->mapdata->door_timers)
			free(data->mapdata->door_timers[i]);
	}
	free(data->mapdata->door_states);
	free(data->mapdata->door_timers);
}

static void	free_mapdata(t_data *data)
{
	if (!data->mapdata)
		return ;
	if (data->mapdata->no_txt_path || data->mapdata->ea_txt_path
		|| data->mapdata->we_txt_path || data->mapdata->so_txt_path
		|| data->mapdata->door_txt_path)
		free_texture_paths(data->mapdata);
	if (data->mapdata->map)
	{
		free_array(data->mapdata->map);
		free_door_arrays(data);
	}
	free(data->mapdata);
}

static void	free_sprite_data(t_data *data)
{
	free_mapdata(data);
	if (!data || !data->sprite)
		return ;
	if (data->sprite->zbuffer)
	{
		free(data->sprite->zbuffer);
		data->sprite->zbuffer = NULL;
	}
	free(data->sprite);
	data->sprite = NULL;
}

int	on_destroy(t_data *data)
{
	if (!data)
		return (1);
	free_layers(data);
	if (data->win_ptr && data->mlx_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		free_texture_resources(data);
		free_sprite_resources(data);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_sprite_data(data);
	if (data->gamestate)
		free(data->gamestate);
	if (data->rays)
		free_rays(data);
	if (data->player)
		free(data->player);
	if (data->input)
		free(data->input);
	if (data->camera)
		free(data->camera);
	free(data);
	return (0);
}
