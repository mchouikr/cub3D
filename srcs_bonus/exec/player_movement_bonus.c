/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:03:35 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 15:30:03 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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

void	update_movement(t_data *data, int ud_direction, int lr_direction)
{
	double	next_x;
	double	next_y;

	next_x = data->player->x_pos;
	next_y = data->player->y_pos;
	next_x = data->player->x_pos + cos(data->player->rot_angle) * ud_direction
		* PLAYER_SPEED;
	next_y = data->player->y_pos + sin(data->player->rot_angle) * ud_direction
		* PLAYER_SPEED;
	next_x = next_x + (cos(data->player->rot_angle + M_PI / 2) * lr_direction
			* PLAYER_SPEED);
	next_y = next_y + (sin(data->player->rot_angle + M_PI / 2) * lr_direction
			* PLAYER_SPEED);
	if (!check_collision(data, next_x, data->player->y_pos))
	{
		data->player->x_pos = next_x;
	}
	if (!check_collision(data, data->player->x_pos, next_y))
	{
		data->player->y_pos = next_y;
	}
}
