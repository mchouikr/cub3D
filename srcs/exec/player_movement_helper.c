/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:05:07 by mchouikr          #+#    #+#             */
/*   Updated: 2025/02/12 14:55:43 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	find_start_pos(t_data *data, t_mapdata *mapdata)
{
	int	x;
	int	y;

	y = 0;
	while (mapdata->map[y])
	{
		x = 0;
		while (mapdata->map[y][x])
		{
			if (mapdata->map[y][x] == 'N' || mapdata->map[y][x] == 'S'
				|| mapdata->map[y][x] == 'E' || mapdata->map[y][x] == 'W')
			{
				data->player->x_pos = x + 0.5f;
				data->player->y_pos = y + 0.5f;
				data->player->start_direction = mapdata->map[y][x];
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	find_start_rot_pos(t_data *data)
{
	if (data->player->start_direction == 'N')
	{
		data->player->rot_angle = 3 * M_PI / 2;
		return (0);
	}
	else if (data->player->start_direction == 'S')
	{
		data->player->rot_angle = M_PI / 2;
		return (0);
	}
	else if (data->player->start_direction == 'E')
	{
		data->player->rot_angle = 0;
		return (0);
	}
	else if (data->player->start_direction == 'W')
	{
		data->player->rot_angle = M_PI;
		return (0);
	}
	return (1);
}

int	check_collision(t_data *data, double next_x, double next_y)
{
	int		map_x;
	int		map_y;
	double	offset;
	int		i;
	int		hitbox[4][2];

	offset = 0.05;
	hitbox[0][0] = next_x - offset;
	hitbox[0][1] = next_y - offset;
	hitbox[1][0] = next_x + offset;
	hitbox[1][1] = next_y - offset;
	hitbox[2][0] = next_x - offset;
	hitbox[2][1] = next_y + offset;
	hitbox[3][0] = next_x + offset;
	hitbox[3][1] = next_y + offset;
	i = 0;
	while (i < 4)
	{
		map_x = (int)hitbox[i][0];
		map_y = (int)hitbox[i][1];
		if (data->mapdata->map[map_y][map_x] == '1')
			return (1);
		i++;
	}
	return (0);
}

void	update_camera_plane(t_data *data, double turn_direction)
{
	double	rotation;
	double	old_dir_x;
	double	old_plane_x;

	rotation = turn_direction * ROTATION_SPEED;
	old_dir_x = data->camera->dir_x;
	old_plane_x = data->camera->plane_x;
	data->camera->dir_x = data->camera->dir_x * cos(rotation)
		- data->camera->dir_y * sin(rotation);
	data->camera->dir_y = old_dir_x * sin(rotation) + data->camera->dir_y
		* cos(rotation);
	data->camera->plane_x = data->camera->plane_x * cos(rotation)
		- data->camera->plane_y * sin(rotation);
	data->camera->plane_y = old_plane_x * sin(rotation) + data->camera->plane_y
		* cos(rotation);
}

void	update_rotation(t_data *data, double turn_direction)
{
	double	next_rotation;

	next_rotation = data->player->rot_angle;
	next_rotation += turn_direction * ROTATION_SPEED;
	data->player->rot_angle = next_rotation;
}
