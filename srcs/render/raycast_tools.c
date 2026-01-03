/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:23:21 by edelplan          #+#    #+#             */
/*   Updated: 2025/01/30 17:48:20 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	is_valid_map_position(t_data *data, int mapx, int mapy)
{
	return (mapx >= 0 && mapx < data->mapdata->width && mapy >= 0
		&& mapy < data->mapdata->height);
}

int	wall_hit(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = floor(x);
	map_y = floor(y);
	if (map_x < 0 || map_y < 0 || map_x >= data->mapdata->width
		|| map_y >= data->mapdata->height)
	{
		on_destroy(data);
		printf("DEBUG: Out of bounds hit at map(%d,%d)\n", map_x, map_y);
		return (1);
	}
	if (data->mapdata->map[map_y]
		&& map_x < (int)ft_strlen(data->mapdata->map[map_y]))
	{
		return (data->mapdata->map[map_y][map_x] == '1');
	}
	return (0);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}
