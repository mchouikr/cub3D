/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:22:53 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/17 15:04:02 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

char	**get_texture_data(char *map, t_mapdata *mapdata)
{
	int		texture_data_end;
	char	**texture_data;
	char	*texture_section;

	texture_data_end = mapdata->start_map;
	texture_data = NULL;
	if (texture_data_end == -1)
		return (ft_fprintf(2, INVALID_MAP), NULL);
	texture_section = ft_substr(map, 0, texture_data_end);
	if (!texture_section)
		return (ft_fprintf(2, INVALID_MAP), NULL);
	texture_data = ft_split(texture_section, '\n');
	free(texture_section);
	if (texture_data == NULL)
		return (ft_fprintf(2, INVALID_MAP), NULL);
	return (texture_data);
}

char	*get_oneline_file(char *str)
{
	int		fd;
	char	*read_map;
	char	*oneline_file;
	char	*tmp;

	fd = 0;
	read_map = NULL;
	oneline_file = NULL;
	if (check_file_format(str, ".cub") == FAILURE)
		return (ft_fprintf(2, INVALID_FILE_EXTENSION), NULL);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_fprintf(2, CANNOT_FIND_OPEN_FILE), NULL);
	oneline_file = ft_calloc(1, sizeof(char));
	if (!oneline_file)
		return (close(fd), NULL);
	tmp = NULL;
	oneline_file = reading_map(read_map, tmp, oneline_file, fd);
	if (oneline_file == NULL || ft_strlen(oneline_file) == 0)
		return (free(oneline_file), close(fd), NULL);
	return (close(fd), oneline_file);
}

int	check_map_validity(char **av, t_mapdata *mapdata)
{
	char	*one_line_file;
	char	**file_array;

	one_line_file = get_oneline_file(av[1]);
	if (!one_line_file)
		return (FAILURE);
	file_array = ft_split(one_line_file, '\n');
	if (!file_array)
		return (free(one_line_file), FAILURE);
	if (check_textures_presence(file_array, mapdata) == FAILURE)
		return (free_array(file_array), free(one_line_file), FAILURE);
	free_array(file_array);
	file_array = NULL;
	file_array = get_texture_data(one_line_file, mapdata);
	if (file_array == NULL)
		return (free_array(file_array), free(one_line_file), FAILURE);
	if (check_textures_data(mapdata, file_array) == FAILURE)
		return (free_array(file_array), free(one_line_file), FAILURE);
	if (check_map_integrity(one_line_file, mapdata) == FAILURE)
		return (free_array(file_array), free(one_line_file), FAILURE);
	if (check_if_closed(one_line_file, mapdata) == FAILURE)
		return (free(one_line_file), free_array(file_array), FAILURE);
	(free(one_line_file), free_array(file_array));
	return (SUCCESS);
}

char	**return_map(char **av, t_mapdata *mapdata)
{
	char	*map;
	char	**map_array;

	map = get_oneline_file(av[1]);
	map_array = create_map_array(map, mapdata);
	if (!map_array)
	{
		ft_printf("Failed to return (map\n");
		exit(EXIT_FAILURE);
	}
	free(map);
	return (map_array);
}
