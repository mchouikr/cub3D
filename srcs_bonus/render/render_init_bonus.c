/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:20:28 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/17 23:42:44 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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

int	init_layers_buffer3(t_data *data)
{
	data->global_layer->img = mlx_new_image(data->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT);
	if (data->global_layer->img == NULL)
		return (FAILURE);
	data->global_layer->addr = mlx_get_data_addr(data->global_layer->img,
			&data->global_layer->bits_per_pixel,
			&data->global_layer->line_length, &data->global_layer->endian);
	if (data->global_layer->addr == NULL)
		return (FAILURE);
	data->sprite_layer->img = mlx_new_image(data->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT);
	if (data->sprite_layer->img == NULL)
		return (FAILURE);
	data->sprite_layer->addr = mlx_get_data_addr(data->sprite_layer->img,
			&data->sprite_layer->bits_per_pixel,
			&data->sprite_layer->line_length, &data->sprite_layer->endian);
	if (data->sprite_layer->addr == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	init_layers_buffer2(t_data *data)
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
	if (init_layers_buffer3(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	init_layers_buffer(t_data *data)
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

void	define_width_and_height(t_data *data)
{
	int	map_width;
	int	map_height;
	int	i;
	int	row_len;

	i = 0;
	map_width = 0;
	map_height = 0;
	while (data->mapdata->map[i])
	{
		row_len = ft_strlen(data->mapdata->map[i]);
		if (row_len > map_width)
			map_width = row_len;
		i++;
	}
	map_width = ft_strlen(data->mapdata->map[1]);
	map_height = ft_tablen(data->mapdata->map);
	data->mapdata->height = map_height;
	data->mapdata->width = map_width;
}
