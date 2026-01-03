/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collisions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 23:01:20 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/17 23:02:00 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static int	check_door_interaction(t_data *data, int map_x, int map_y)
{
	if (data->input->space_pressed == 1)
	{
		if (data->mapdata->door_states[map_y][map_x] == CLOSED)
		{
			data->mapdata->door_states[map_y][map_x] = OPENING;
			return (1);
		}
	}
	if (data->mapdata->door_states[map_y][map_x] == CLOSED
		|| data->mapdata->door_states[map_y][map_x] == OPENING
		|| data->mapdata->door_states[map_y][map_x] == CLOSING
		|| data->mapdata->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

static void	init_hitbox(int hitbox[4][2], double next_x, double next_y)
{
	double	offset;

	offset = 0.3;
	hitbox[0][0] = next_x - offset;
	hitbox[0][1] = next_y - offset;
	hitbox[1][0] = next_x + offset;
	hitbox[1][1] = next_y - offset;
	hitbox[2][0] = next_x - offset;
	hitbox[2][1] = next_y + offset;
	hitbox[3][0] = next_x + offset;
	hitbox[3][1] = next_y + offset;
}

int	check_collision(t_data *data, double next_x, double next_y)
{
	int	map_x;
	int	map_y;
	int	i;
	int	hitbox[4][2];

	init_hitbox(hitbox, next_x, next_y);
	i = 0;
	while (i < 4)
	{
		map_x = (int)hitbox[i][0];
		map_y = (int)hitbox[i][1];
		if (data->mapdata->map[map_y][map_x] == '1')
			return (1);
		if (data->mapdata->door_states[map_y][map_x] != -1
			&& check_door_interaction(data, map_x, map_y))
			return (1);
		if (data->mapdata->map[map_y][map_x] == 'C')
		{
			data->mapdata->map[map_y][map_x] = '0';
			data->gamestate->c_count--;
		}
		i++;
	}
	return (0);
}
