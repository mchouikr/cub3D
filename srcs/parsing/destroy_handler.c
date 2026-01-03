/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:38:26 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 00:33:39 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	on_destroy_helper(t_data *data)
{
	if (data->mapdata)
	{
		if (data->mapdata->no_txt_path || data->mapdata->ea_txt_path
			|| data->mapdata->we_txt_path || data->mapdata->so_txt_path)
			free_texture_paths(data->mapdata);
		if (data->mapdata->map)
			free_array(data->mapdata->map);
		free(data->mapdata);
		data->mapdata = NULL;
	}
	free_layers(data);
	if (data->rays)
		free_rays(data);
	if (data->player != NULL)
		free(data->player);
	if (data->input)
		free(data->input);
	if (data->camera)
		free(data->camera);
	if (data)
		free(data);
}

int	on_destroy(t_data *data)
{
	if (!data)
		return (1);
	free_layers(data);
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	if (data->mlx_ptr)
	{
		free_textures_buffer(data);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		data->mlx_ptr = NULL;
	}
	on_destroy_helper(data);
	exit(0);
}
