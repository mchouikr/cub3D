/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_helper2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 23:32:30 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 15:51:58 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static int	get_step_direction(int start, int end)
{
	if (start < end)
		return (1);
	return (-1);
}

static void	init_ray_line(t_line *line, t_ray_pos *pos)
{
	line->x1 = (int)pos->start_x;
	line->y1 = (int)pos->start_y;
	line->x2 = (int)pos->end_x;
	line->y2 = (int)pos->end_y;
	line->color = 0xFFFF01;
	line->dx = abs(line->x2 - line->x1);
	line->dy = abs(line->y2 - line->y1);
	line->sx = get_step_direction(line->x1, line->x2);
	line->sy = get_step_direction(line->y1, line->y2);
	line->err = 0;
}

void	draw_rays(t_data *data, int player_x, int player_y, float tile_size)
{
	t_line		line;
	t_ray_pos	pos;
	int			i;
	int			border_x;
	int			border_y;

	border_x = 100 - (12 * tile_size) / 2;
	border_y = 100 - (12 * tile_size) / 2;
	pos.start_x = player_x;
	pos.start_y = player_y;
	i = 0;
	while (i < NUM_RAYS)
	{
		pos.end_x = player_x + (data->rays[i].wall_hit_x * tile_size);
		pos.end_y = player_y + (data->rays[i].wall_hit_y * tile_size);
		pos.end_x = fmin(fmax(pos.end_x, border_x), border_x + (12
					* tile_size));
		pos.end_y = fmin(fmax(pos.end_y, border_y), border_y + (12
					* tile_size));
		init_ray_line(&line, &pos);
		draw_line(data->ray_layer, line);
		i++;
	}
}

void	draw_player(t_data *data, int screen_x, int screen_y)
{
	t_rect	rect;
	int		layer_size;
	float	player_size;

	player_size = PLAYER_SIZE * MINIMAP_SCALE;
	layer_size = ((int)player_size * (int)player_size)
		* (data->player_layer->bits_per_pixel / 8);
	clear_layer(data->player_layer, layer_size);
	rect = (t_rect){screen_x - player_size / 2, screen_y - player_size / 2,
		player_size, 0xFF0000};
	mlx_put_rectangle_to_layer(data->ray_layer, rect);
}

void	draw_ray_hit(t_data *data)
{
	int		b_size;
	float	t_size;
	int		center_x;
	int		center_y;

	center_x = 100;
	center_y = 100;
	t_size = TILE_SIZE * MINIMAP_SCALE;
	b_size = 12 * t_size;
	clear_layer(data->ray_layer, WIN_HEIGHT * WIN_WIDTH);
	clear_layer(data->map_layer, WIN_HEIGHT * WIN_WIDTH);
	draw_minimap_border(data, center_x - b_size / 2, center_y - b_size / 2,
		b_size);
	draw_map_tiles(data, t_size, center_x - b_size / 2, center_y - b_size / 2);
	draw_rays(data, center_x, center_y, t_size);
	draw_player(data, center_x, center_y);
}
