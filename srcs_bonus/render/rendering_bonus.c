/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:19:04 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/13 19:38:26 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

// CREE LE LAYER GLOBAL DE L"IMAGE SUPERPOSANT TOUT ENSEMBLE !!

static void	mix_layers(t_pixels *pixels)
{
	if (*(unsigned int *)pixels->wall != 0
		&& *(unsigned int *)pixels->wall != 0x000000)
	{
		*(unsigned int *)pixels->global = (*(unsigned int *)pixels->wall);
	}
	if (*(unsigned int *)pixels->sprite != 0
		&& *(unsigned int *)pixels->sprite != 0x000000)
	{
		*(unsigned int *)pixels->global = (*(unsigned int *)pixels->sprite);
	}
	if (*(unsigned int *)pixels->map != 0
		&& *(unsigned int *)pixels->map != 0x000000)
	{
		*(unsigned int *)pixels->global = (*(unsigned int *)pixels->map);
	}
	if (*(unsigned int *)pixels->ray != 0
		&& *(unsigned int *)pixels->ray != 0x000000)
	{
		*(unsigned int *)pixels->global = (*(unsigned int *)pixels->ray
				& 0xdbd646);
	}
}

static void	get_pixel_and_mix(t_data *data, int x, int y)
{
	t_pixels	pixels;

	pixels.ray = data->ray_layer->addr + (y * data->ray_layer->line_length
			+ x * (data->ray_layer->bits_per_pixel / 8));
	pixels.map = data->map_layer->addr + (y * data->map_layer->line_length
			+ x * (data->map_layer->bits_per_pixel / 8));
	pixels.wall = data->wall_layer->addr + (y
			* data->wall_layer->line_length + x
			* (data->wall_layer->bits_per_pixel / 8));
	pixels.global = data->global_layer->addr + (y
			* data->global_layer->line_length + x
			* (data->global_layer->bits_per_pixel / 8));
	pixels.sprite = data->sprite_layer->addr + (y
			* data->sprite_layer->line_length + x
			* (data->sprite_layer->bits_per_pixel / 8));
	mix_layers(&pixels);
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
	int	y;
	int	x;

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
