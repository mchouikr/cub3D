/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:19:04 by edelplan          #+#    #+#             */
/*   Updated: 2025/01/30 18:38:23 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// CREE LE LAYER GLOBAL DE L"IMAGE SUPERPOSANT TOUT ENSEMBLE !!

static void	mix_layers(char *ray_pixel, char *map_pixel, char *wall_pixel,
		char *global_pixel)
{
	if (*(unsigned int *)wall_pixel != 0
		&& *(unsigned int *)wall_pixel != 0x000000)
	{
		*(unsigned int *)global_pixel = (*(unsigned int *)wall_pixel);
	}
	if (*(unsigned int *)map_pixel != 0
		&& *(unsigned int *)map_pixel != 0x000000)
	{
		*(unsigned int *)global_pixel = (*(unsigned int *)map_pixel);
	}
	if (*(unsigned int *)ray_pixel != 0
		&& *(unsigned int *)ray_pixel != 0x000000)
	{
		*(unsigned int *)global_pixel = (*(unsigned int *)ray_pixel & 0xdbd646);
	}
}

static void	get_pixel_and_mix(t_data *data, int x, int y)
{
	char	*ray_pixel;
	char	*map_pixel;
	char	*wall_pixel;
	char	*global_pixel;

	ray_pixel = data->ray_layer->addr + (y * data->ray_layer->line_length + x
			* (data->ray_layer->bits_per_pixel / 8));
	map_pixel = data->map_layer->addr + (y * data->map_layer->line_length + x
			* (data->map_layer->bits_per_pixel / 8));
	wall_pixel = data->wall_layer->addr + (y * data->wall_layer->line_length + x
			* (data->wall_layer->bits_per_pixel / 8));
	global_pixel = data->global_layer->addr + (y
			* data->global_layer->line_length + x
			* (data->global_layer->bits_per_pixel / 8));
	mix_layers(ray_pixel, map_pixel, wall_pixel, global_pixel);
}

void	cast_rays(t_data *data)
{
	int		ray_id;
	double	fov_rad;
	double	ray_angle;
	double	angle_step;

	ray_id = 0;
	fov_rad = (FOV * M_PI) / 180.0;
	ray_angle = data->player->rot_angle - (fov_rad / 2);
	angle_step = fov_rad / NUM_RAYS;
	while (ray_id < NUM_RAYS)
	{
		data->rays[ray_id].angle = ray_angle;
		cast_single_ray(data, &data->rays[ray_id], ray_id);
		ray_angle = ray_angle + angle_step;
		ray_id++;
	}
}

void	create_comp(t_data *data)
{
	int		y;
	int		x;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			get_pixel_and_mix(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->global_layer->img, 0, 0);
}
