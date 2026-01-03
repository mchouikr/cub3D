/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_handler_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:33:14 by edelplan          #+#    #+#             */
/*   Updated: 2025/01/30 19:42:06 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_texture_paths(t_mapdata *mapdata)
{
	if (mapdata->no_txt_path)
		free(mapdata->no_txt_path);
	if (mapdata->so_txt_path)
		free(mapdata->so_txt_path);
	if (mapdata->we_txt_path)
		free(mapdata->we_txt_path);
	if (mapdata->ea_txt_path)
		free(mapdata->ea_txt_path);
	mapdata->no_txt_path = NULL;
	mapdata->so_txt_path = NULL;
	mapdata->we_txt_path = NULL;
	mapdata->ea_txt_path = NULL;
}

void	free_rays(t_data *data)
{
	if (data && data->rays)
	{
		free(data->rays);
		data->rays = NULL;
	}
}

void	free_single_layer(void *mlx, t_img *layer)
{
	if (!mlx || !layer)
		return ;
	if (layer->img)
	{
		mlx_destroy_image(mlx, layer->img);
		layer->img = NULL;
		layer->addr = NULL;
	}
	free(layer);
}

void	free_layers(t_data *data)
{
	if (!data || !data->mlx_ptr)
		return ;
	free_single_layer(data->mlx_ptr, data->map_layer);
	free_single_layer(data->mlx_ptr, data->player_layer);
	free_single_layer(data->mlx_ptr, data->ray_layer);
	free_single_layer(data->mlx_ptr, data->wall_layer);
	free_single_layer(data->mlx_ptr, data->global_layer);
	data->map_layer = NULL;
	data->player_layer = NULL;
	data->ray_layer = NULL;
	data->wall_layer = NULL;
	data->global_layer = NULL;
}

void	free_textures_buffer(t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i < 4)
	{
		if (data->textures_buffer[i])
		{
			if (data->textures_buffer[i]->img)
				mlx_destroy_image(data->mlx_ptr, data->textures_buffer[i]->img);
			free(data->textures_buffer[i]);
		}
		i++;
	}
}
