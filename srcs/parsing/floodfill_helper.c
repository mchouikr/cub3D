/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:37:43 by mchouikr          #+#    #+#             */
/*   Updated: 2025/02/10 19:40:53 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	is_valid_coord(char **map, int x, int y)
{
	size_t	line_len;

	if (x < 0 || y < 0)
		return (false);
	if (!map[y])
		return (false);
	line_len = ft_strlen(map[y]);
	if (x < 0 || x >= (int)line_len)
		return (false);
	return (true);
}

bool	is_valid_pos(char **map_array, int x, int y)
{
	if (!map_array[y])
		return (false);
	if (x < 0 || y < 0 || !map_array[y][x])
		return (false);
	return (true);
}
