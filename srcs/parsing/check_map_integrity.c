/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_integrity.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:35:47 by edelplan          #+#    #+#             */
/*   Updated: 2026/01/03 16:20:33 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	count_char(char *map, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (map[i])
	{
		if (map[i] == c)
			count++;
		i++;
	}
	return (count);
}

static bool	is_empty_line(char *map, int i)
{
	while (map[i] && map[i] != '\n')
	{
		if (map[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

static int	check_start_pos(char *map, t_mapdata *mapdata, int i)
{
	i = mapdata->start_map;
	if ((count_char(&map[i], 'N') + count_char(&map[i], 'S')
			+ count_char(&map[i], 'E') + count_char(&map[i], 'W')) != 1)
		return (ft_fprintf(2, INVALID_START_POS_AMOUNT), FAILURE);
	return (SUCCESS);
}

int	check_map_integrity(char *map, t_mapdata *mapdata)
{
	int	i;

	if (mapdata == NULL || map == NULL || mapdata->start_map == -1
		|| mapdata->start_map > (int)ft_strlen(map))
		return (ft_fprintf(2, NO_MAP_FOUND), FAILURE);
	i = mapdata->start_map;
	while (i < (int)ft_strlen(map) && ft_isspace(map[i]))
		i++;
	if (i == (int)ft_strlen(map))
		return (ft_fprintf(2, NO_MAP_FOUND), FAILURE);
	while (i < (int)ft_strlen(map))
	{
		if (map[i] != '1' && map[i] != '0' && map[i] != 'N' && map[i] != 'S'
			&& map[i] != 'E' && map[i] != 'W' && map[i] != ' '
			&& map[i] != '\n')
			return (ft_fprintf(2, INVALID_MAP_SYMBOLS), FAILURE);
		if ((map[i] == '\n' && map[i + 1] == '\n') || (map[i] == '\n'
				&& is_empty_line(map, i + 1)))
			return (ft_fprintf(2, EMPTY_LINE_IN_MAP), FAILURE);
		i++;
	}
	if (check_start_pos(map, mapdata, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
