/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:02:03 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 00:05:27 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	draw_wall_tile(t_data *data, float ts, int pos_x, int pos_y)
{
	t_rect	rect;

	rect.x = pos_x - ts / 2;
	rect.y = pos_y - ts / 2;
	rect.size = ts;
	rect.color = convert_to_hex(data->mapdata->f_rgb);
	mlx_put_rectangle_to_layer(data->map_layer, rect);
}

static bool	is_valid_map_position(t_data *data, t_map_pos *pos)
{
	if (pos->x < 0 || pos->y < 0)
		return (false);
	if (pos->y >= data->mapdata->height)
		return (false);
	if (pos->x >= (int)ft_strlen(data->mapdata->map[pos->y]))
		return (false);
	return (true);
}

static void	process_map_tile(t_data *data, t_map_pos *pos, float ts)
{
	int	screen_x;
	int	screen_y;

	if (!is_valid_map_position(data, pos))
		return ;
	screen_x = 100 + ((pos->x - data->player->x_pos) * ts) + (ts / 2);
	screen_y = 100 + ((pos->y - data->player->y_pos) * ts) + (ts / 2);
	if (screen_x - ts / 2 >= pos->bx && screen_x + ts / 2 <= pos->bx + 12 * ts
		&& screen_y - ts / 2 >= pos->by && screen_y + ts / 2 <= pos->by + 12
		* ts)
	{
		if (data->mapdata->map[pos->y][pos->x] == '1')
			draw_wall_tile(data, ts, screen_x, screen_y);
		else if (data->mapdata->map[pos->y][pos->x] == 'C')
			draw_coins(data, screen_x, screen_y, ts);
	}
}

void	draw_map_tiles(t_data *data, float ts, int bord_x, int bord_y)
{
	t_map_pos	pos;
	int			start_y;
	int			end_y;

	start_y = fmax(0, (int)data->player->y_pos - 6);
	end_y = fmin((int)data->player->y_pos + 6, data->mapdata->height);
	pos.by = bord_y;
	pos.bx = bord_x;
	pos.y = start_y;
	while (pos.y < end_y)
	{
		pos.x = fmax(0, (int)data->player->x_pos - 6);
		while (pos.x < fmin((int)data->player->x_pos + 6, data->mapdata->width))
		{
			process_map_tile(data, &pos, ts);
			pos.x++;
		}
		pos.y++;
	}
}
