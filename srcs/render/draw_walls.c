/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:34:46 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/13 19:10:07 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_wall_stripe(t_data *data, int ray_id, t_wall wall, int tex_num)
{
	void	*tex_data;
	double	step;
	double	pos;
	int		tex_y;

	tex_data = mlx_get_data_addr(data->textures_buffer[tex_num]->img,
			&data->textures_buffer[tex_num]->bits_per_pixel,
			&data->textures_buffer[tex_num]->line_length,
			&data->textures_buffer[tex_num]->endian);
	if (!tex_data)
		return ;
	step = 1.0 * TILE_SIZE / wall.height;
	pos = (wall.start - WIN_HEIGHT / 2 + wall.height / 2) * step;
	while (wall.start < wall.end)
	{
		tex_y = ((int)pos & (TILE_SIZE - 1));
		pos += step;
		if (tex_y >= 0 && tex_y < TILE_SIZE)
			put_pixel_to_layer(data->wall_layer, ray_id, wall.start,
				get_texture_color(tex_data, wall.tex_x, tex_y));
		wall.start++;
	}
}

void	project_walls(t_data *data)
{
	t_wall	wall;
	int		ray_id;
	int		tex_num;

	project_ceiling_floor(data);
	ray_id = 0;
	while (ray_id < NUM_RAYS)
	{
		calculate_wall_bounds(data->rays[ray_id], &wall.start, &wall.end,
			&wall.height);
		tex_num = get_texture_number(data->rays[ray_id]);
		wall.wall_x = calculate_wall_x(data, data->rays[ray_id]);
		wall.tex_x = (int)(wall.wall_x * TILE_SIZE);
		if (!data->rays[ray_id].hit_vertical
			&& data->rays[ray_id].ray_dir_x < 0)
			wall.tex_x = TILE_SIZE - wall.tex_x - 1;
		if (data->rays[ray_id].hit_vertical && data->rays[ray_id].ray_dir_y > 0)
			wall.tex_x = TILE_SIZE - wall.tex_x - 1;
		draw_wall_stripe(data, ray_id, wall, tex_num);
		ray_id++;
	}
}
