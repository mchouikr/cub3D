/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:55:58 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/17 23:41:58 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	handle_open_door(t_data *data, int map_y, int map_x, double dt)
{
	double	door_center_x;
	double	door_center_y;
	double	dist_to_player;

	data->mapdata->door_timers[map_y][map_x] += dt;
	door_center_x = map_x + 0.5;
	door_center_y = map_y + 0.5;
	dist_to_player = sqrt(pow(data->player->x_pos - door_center_x, 2)
			+ pow(data->player->y_pos - door_center_y, 2));
	if (data->mapdata->door_timers[map_y][map_x] >= 3.5 && dist_to_player > 1.0)
	{
		data->mapdata->door_states[map_y][map_x] = CLOSING;
		data->mapdata->door_timers[map_y][map_x] = 0.0;
	}
}

static void	update_door_state(t_data *data, int map_y, int map_x, double dt)
{
	if (data->mapdata->door_states[map_y][map_x] == OPENING)
	{
		data->mapdata->door_timers[map_y][map_x] += dt;
		if (data->mapdata->door_timers[map_y][map_x] >= 1.0)
		{
			data->mapdata->door_states[map_y][map_x] = OPEN;
			data->mapdata->door_timers[map_y][map_x] = 0.0;
		}
	}
	else if (data->mapdata->door_states[map_y][map_x] == OPEN)
		handle_open_door(data, map_y, map_x, dt);
	else if (data->mapdata->door_states[map_y][map_x] == CLOSING)
	{
		data->mapdata->door_timers[map_y][map_x] += dt;
		if (data->mapdata->door_timers[map_y][map_x] >= 1.0)
		{
			data->mapdata->door_states[map_y][map_x] = CLOSED;
			data->mapdata->door_timers[map_y][map_x] = 0.0;
			data->mapdata->door_active = false;
		}
	}
}

static bool	is_valid_map_position(t_data *data, int map_y, int map_x)
{
	if (map_x < 0 || map_y < 0)
		return (false);
	if (map_y >= data->mapdata->height)
		return (false);
	if (!data->mapdata->map[map_y])
		return (false);
	if (map_x >= (int)ft_strlen(data->mapdata->map[map_y]))
		return (false);
	return (true);
}

void	update_door_animation(t_data *data, double dt)
{
	int	map_y;
	int	map_x;

	if (!data || !data->mapdata || !data->mapdata->map
		|| !data->mapdata->door_states || !data->mapdata->door_timers)
		return ;
	map_y = 0;
	while (map_y < data->mapdata->height)
	{
		map_x = 0;
		while (map_x < data->mapdata->width)
		{
			if (is_valid_map_position(data, map_y, map_x)
				&& data->mapdata->map[map_y][map_x] == 'D')
			{
				update_door_state(data, map_y, map_x, dt);
			}
			map_x++;
		}
		map_y++;
	}
}
