/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:10:54 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/17 10:40:14 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	check_empty_lines(char *map)
{
	int	i;

	i = 0;
	if (map[0] == '\n')
	{
		free(map);
		ft_fprintf(2, EMPTY_LINE_IN_MAP);
		return (FAILURE);
	}
	while (map[i] != '\0')
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
		{
			free(map);
			ft_fprintf(2, EMPTY_LINE_IN_MAP);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
