/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:40:38 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 00:43:39 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_array(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i] != NULL)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

int	convert_to_hex(int *rgb_value)
{
	int	r;
	int	g;
	int	b;

	r = rgb_value[0];
	g = rgb_value[1];
	b = rgb_value[2];
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

bool	set_texture_path(t_mapdata *mapdata, char *line, const char *identifier)
{
	char	*path;

	path = get_texture_path(line, identifier);
	if (!path)
		return (false);
	if (!ft_strncmp(identifier, "NO ", 3))
		mapdata->no_txt_path = path;
	else if (!ft_strncmp(identifier, "SO ", 3))
		mapdata->so_txt_path = path;
	else if (!ft_strncmp(identifier, "WE ", 3))
		mapdata->we_txt_path = path;
	else if (!ft_strncmp(identifier, "EA ", 3))
		mapdata->ea_txt_path = path;
	else
	{
		free(path);
		return (false);
	}
	return (true);
}
