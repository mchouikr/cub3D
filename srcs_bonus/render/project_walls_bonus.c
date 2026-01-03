/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:54 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/13 19:36:51 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	get_texture_color(void *tex_data, int tex_num, int x, int y)
{
	unsigned char	*addr;
	int				offset;
	unsigned int	color;

	addr = (unsigned char *)tex_data;
	offset = (y * TILE_SIZE + x) * 4;
	color = *(unsigned int *)(addr + offset);
	if (tex_num == NORTH || tex_num == SOUTH)
		color = (color >> 1) & 0x7F7F7F;
	if (color == 0)
		color = 1;
	if (color == 0x000000)
		color = 1;
	return (color);
}

void	project_ceiling_floor(t_data *data)
{
	int	f_color;
	int	c_color;
	int	y;
	int	x;

	f_color = convert_to_hex(data->mapdata->f_rgb);
	c_color = convert_to_hex(data->mapdata->c_rgb);
	if (f_color == 0x000000)
		f_color += 1;
	if (c_color == 0x000000)
		c_color += 1;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				put_pixel_to_layer(data->wall_layer, x, y, c_color);
			else
				put_pixel_to_layer(data->wall_layer, x, y, f_color);
			x++;
		}
		y++;
	}
}

void	calculate_wall_bounds(t_ray ray, int *start, int *end, int *height)
{
	*height = (int)(WIN_HEIGHT / ray.distance);
	*start = -(*height) / 2 + WIN_HEIGHT / 2;
	*end = (*height) / 2 + WIN_HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	if (*end >= WIN_HEIGHT)
		*end = WIN_HEIGHT - 1;
}

int	get_texture_number(t_ray ray)
{
	if (ray.hit_vertical == 0)
	{
		if (ray.door_hit == 1)
			return (DOOR);
		if (ray.ray_dir_x < 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (ray.door_hit == 1)
			return (DOOR);
		if (ray.ray_dir_y < 0)
			return (NORTH);
		else
			return (SOUTH);
	}
}

double	calculate_wall_x(t_data *data, t_ray ray)
{
	double	wall_x;

	if (ray.hit_vertical == 0)
		wall_x = data->player->y_pos + ray.distance * ray.ray_dir_y;
	else
		wall_x = data->player->x_pos + ray.distance * ray.ray_dir_x;
	return (wall_x - floor(wall_x));
}

// void	project_walls(t_data *data)
// {
// 	project_ceiling_floor(data);

// 	int ray_id = 0;
// 	while (ray_id < NUM_RAYS)
// 	{
// 		int line_height = (int)(WIN_HEIGHT / data->rays[ray_id].distance);
// 		int draw_start = -line_height / 2 + WIN_HEIGHT / 2;
// 		if (draw_start < 0)
// 			draw_start = 0;
// 		int draw_end = line_height / 2 + WIN_HEIGHT / 2;
// 		if (draw_end >= WIN_HEIGHT)
// 			draw_end = WIN_HEIGHT - 1;

// 		int textNum;
// 		if (data->rays[ray_id].hit_vertical == 0)
// 		{
// 			if (data->rays[ray_id].ray_dir_x < 0)
// 				textNum = WEST;  // West wall
// 			else
// 				textNum = EAST;  // East wall
// 		}
// 		else
// 		{
// 			if (data->rays[ray_id].ray_dir_y < 0)
// 				textNum = NORTH; // North wall
// 			else
// 				textNum = SOUTH; // South wall
// 		}
// 		double wall_x;
// 		if (data->rays[ray_id].hit_vertical == 0)
// // 			wall_x = data->player->y_pos + data->rays[ray_id].distance
// 				* data->rays[ray_id].ray_dir_y;
// // 		else
// // 		{
// // 			wall_x = data->player->x_pos + data->rays[ray_id].distance
// 				* data->rays[ray_id].ray_dir_x;
// // 		}
// // 		wall_x -= floor(wall_x);

// // 		int tex_x;
// // 		tex_x = (int)(wall_x * (double)TILE_SIZE);
// // 		if (data->rays[ray_id].hit_vertical == 0
// 			&& data->rays[ray_id].ray_dir_x < 0)
// // 			tex_x = TILE_SIZE - tex_x - 1;
// // 		if (data->rays[ray_id].hit_vertical == 1
// 			&& data->rays[ray_id].ray_dir_y > 0)
// // 			tex_x = TILE_SIZE - tex_x - 1;

//  	double step = 1.0 * TILE_SIZE / line_height;
//     double pos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step;

// void *tex_data = mlx_get_data_addr(data->textures_buffer[textNum]->img,
//                           &data->textures_buffer[textNum]->bits_per_pixel,
//                             &data->textures_buffer[textNum]->line_length,
//                             &data->textures_buffer[textNum]->endian);

// 	if (tex_data)
// 	{
// // 		while (draw_start < draw_end)
// // 		{
// // 			int tex_y = ((int)pos & (TILE_SIZE - 1));
// // 			pos += step;
// // 			int color_pos = (tex_y
// 					* data->textures_buffer[textNum]->line_length) + (tex_x
// 					* (data->textures_buffer[textNum]->bits_per_pixel / 8));
// // 			if (color_pos >= 0 && color_pos < (TILE_SIZE
// 					* data->textures_buffer[textNum]->line_length))
// // 			{
// // 				unsigned int color = *(unsigned int*)(tex_data + color_pos);
// // 				if(textNum 	== 1 || textNum == 0)
// // 					color = (color >> 1) & 0x7F7F7F;
// // 				if (color == 0)
// // 					color += 1;
// // 				if (color > 0  && color != 0x000000)
// // 					put_pixel_to_layer(data->wall_layer, ray_id, draw_start,
// 						color);
// // 			}
// // 			draw_start++;
// // 		}
// //     }
// // 		ray_id++;
// // 	}
// // }