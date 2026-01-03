/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:20:28 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/13 19:06:06 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_tablen(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static int	init_layers_buffer2(t_data *data)
{
	data->ray_layer->addr = mlx_get_data_addr(data->ray_layer->img,
			&data->ray_layer->bits_per_pixel, &data->ray_layer->line_length,
			&data->ray_layer->endian);
	if (data->ray_layer->addr == NULL)
		return (FAILURE);
	data->wall_layer->img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (data->wall_layer->img == NULL)
		return (FAILURE);
	data->wall_layer->addr = mlx_get_data_addr(data->wall_layer->img,
			&data->wall_layer->bits_per_pixel, &data->wall_layer->line_length,
			&data->wall_layer->endian);
	if (data->wall_layer->addr == NULL)
		return (FAILURE);
	data->global_layer->img = mlx_new_image(data->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT);
	if (data->global_layer->img == NULL)
		return (FAILURE);
	data->global_layer->addr = mlx_get_data_addr(data->global_layer->img,
			&data->global_layer->bits_per_pixel,
			&data->global_layer->line_length, &data->global_layer->endian);
	if (data->global_layer->addr == NULL)
		return (FAILURE);
	return (SUCCESS);
}

static int	init_layers_buffer(t_data *data)
{
	data->map_layer->img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (data->map_layer->img == NULL)
		return (FAILURE);
	data->map_layer->addr = mlx_get_data_addr(data->map_layer->img,
			&data->map_layer->bits_per_pixel, &data->map_layer->line_length,
			&data->map_layer->endian);
	if (data->map_layer->addr == NULL)
		return (FAILURE);
	data->player_layer->img = mlx_new_image(data->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT);
	if (data->player_layer->img == NULL)
		return (FAILURE);
	data->player_layer->addr = mlx_get_data_addr(data->player_layer->img,
			&data->player_layer->bits_per_pixel,
			&data->player_layer->line_length, &data->player_layer->endian);
	if (data->player_layer->addr == NULL)
		return (FAILURE);
	data->ray_layer->img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (data->ray_layer->img == NULL)
		return (FAILURE);
	if (init_layers_buffer2(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	init_layers(t_data *data)
{
	int	map_width;
	int	map_height;

	map_width = ft_strlen(data->mapdata->map[0]) * TILE_SIZE;
	map_height = ft_tablen(data->mapdata->map) * TILE_SIZE;
	data->mapdata->height = map_height;
	data->mapdata->width = map_width;
	data->map_layer = malloc(sizeof(t_img));
	if (data->map_layer == NULL)
		return (FAILURE);
	data->player_layer = malloc(sizeof(t_img));
	if (data->player_layer == NULL)
		return (FAILURE);
	data->ray_layer = malloc(sizeof(t_img));
	if (data->ray_layer == NULL)
		return (FAILURE);
	data->wall_layer = malloc(sizeof(t_img));
	if (data->wall_layer == NULL)
		return (FAILURE);
	data->global_layer = malloc(sizeof(t_img));
	if (data->global_layer == NULL)
		return (FAILURE);
	if (init_layers_buffer(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
