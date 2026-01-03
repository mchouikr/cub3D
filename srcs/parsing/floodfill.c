/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:45:38 by edelplan          #+#    #+#             */
/*   Updated: 2026/01/03 16:18:04 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	**create_map_array(char *map, t_mapdata *mapdata)
{
	char	**map_array;
	int		start_index;

	start_index = mapdata->start_map;
	if (start_index == -1)
	{
		ft_printf("Error\nFailed to find valid map\n");
		free(map);
		exit(EXIT_FAILURE);
	}
	map_array = ft_split(&map[start_index], '\n');
	if (!map_array)
	{
		ft_printf("Error\nFailed to parse map\n");
		exit(EXIT_FAILURE);
	}
	return (map_array);
}

bool	flood_fill(char **map, int x, int y)
{
	if (!is_valid_coord(map, x, y))
		return (false);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (true);
	if (ft_isspace(map[y][x]))
		return (false);
	map[y][x] = 'V';
	return (flood_fill(map, x, y - 1) && flood_fill(map, x - 1, y)
		&& flood_fill(map, x, y + 1) && flood_fill(map, x + 1, y));
}

bool	check_zero_neighbors(char **map_array, int x, int y)
{
	if (ft_isspace(map_array[y][x]))
		return (false);
	if (!is_valid_pos(map_array, x, y - 1) || ft_isspace(map_array[y][x + 1]
		|| !is_valid_pos(map_array, x + 1, y) || ft_isspace(map_array[y][x
			- 1]) || !is_valid_pos(map_array, x, y + 1)
		|| ft_isspace(map_array[y + 1][x]) || !is_valid_pos(map_array, x
			- 1, y) || ft_isspace(map_array[y - 1][x])))
		return (false);
	return (true);
}

bool	flood_fill_map(char **map_array)
{
	int	y;
	int	x;

	y = 0;
	while (map_array[y])
	{
		x = 0;
		while (map_array[y][x])
		{
			if (map_array[y][x] == '0')
				if (!flood_fill(map_array, x, y))
					return (false);
			x++;
		}
		y++;
	}
	return (true);
}

int	check_if_closed(char *map, t_mapdata *mapdata)
{
	char	**map_array;
	int		y;
	bool	is_valid;
	int		x;

	map_array = create_map_array(map, mapdata);
	y = -1;
	is_valid = true;
	while (map_array[++y] && is_valid)
	{
		x = -1;
		while (map_array[y][++x] && is_valid)
		{
			if (map_array[y][x] == '0' || map_array[y][x] == 'N'
				|| map_array[y][x] == 'S' || map_array[y][x] == 'E'
				|| map_array[y][x] == 'W' || map_array[y][x] == 'D' || map_array[y][x] == 'C')
			{
				if (!flood_fill(map_array, x, y))
					is_valid = false;
			}
		}
	}
	if (!is_valid)
		return (ft_fprintf(2, MAP_NOT_CLOSED), free_array(map_array), FAILURE);
	return (free_array(map_array), SUCCESS);
}
