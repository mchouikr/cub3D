/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:52:58 by mchouikr          #+#    #+#             */
/*   Updated: 2025/02/18 17:43:37 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*get_texture_path(char *line, const char *identifier)
{
	int		i;
	int		start;
	int		end;
	char	*path;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	i += ft_strlen(identifier);
	while (ft_isspace(line[i]))
		i++;
	start = i;
	end = ft_strlen(line);
	while (end > start && ft_isspace(line[end - 1]))
		end--;
	path = ft_substr(line, start, end - start);
	if (!path)
	{
		return (NULL);
	}
	return (path);
}

static bool	process_rgb_component(char *value, int *result)
{
	char	*trimmed;
	int		tmp;
	int		i;

	i = 0;
	trimmed = ft_strtrim(value, " \t\n\r");
	if (!trimmed)
		return (false);
	while (trimmed[i])
	{
		if (!ft_isdigit(trimmed[i]))
			return (free(trimmed), false);
		i++;
	}
	tmp = ft_atoi(trimmed);
	free(trimmed);
	if (tmp < 0 || tmp > 255)
		return (false);
	*result = tmp;
	return (true);
}

static bool	parse_rgb_value(char *str, int rgb[3])
{
	char	**values;
	int		i;

	i = 0;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == 'F' || *str == 'C')
		str++;
	while (*str && ft_isspace(*str))
		str++;
	if (check_virgules(str) == FAILURE)
		return (false);
	values = ft_split(str, ',');
	if (!values || ft_tablen(values) > 3)
		return (false);
	while (values[i] && i < 3)
	{
		if (!process_rgb_component(values[i], &rgb[i]))
			return (free_array(values), false);
		i++;
	}
	free_array(values);
	return (i == 3);
}

static int	process_texture_line(t_mapdata *mapdata, char *line)
{
	int	j;

	j = 0;
	while (ft_isspace(line[j]))
		j++;
	if (!ft_strncmp(&line[j], "NO ", 3))
		set_texture_path(mapdata, &line[j], "NO ");
	else if (!ft_strncmp(&line[j], "SO ", 3))
		set_texture_path(mapdata, &line[j], "SO ");
	else if (!ft_strncmp(&line[j], "WE ", 3))
		set_texture_path(mapdata, &line[j], "WE ");
	else if (!ft_strncmp(&line[j], "EA ", 3))
		set_texture_path(mapdata, &line[j], "EA ");
	else if (!ft_strncmp(&line[j], "F ", 2))
	{
		if (!parse_rgb_value(&line[j], mapdata->f_rgb))
			return (ft_fprintf(2, INVALID_FLOOR_COLOR), FAILURE);
	}
	else if (!ft_strncmp(&line[j], "C ", 2))
	{
		if (!parse_rgb_value(&line[j], mapdata->c_rgb))
			return (ft_fprintf(2, INVALID_CEILING_COLOR), FAILURE);
	}
	return (SUCCESS);
}

int	check_textures_data(t_mapdata *mapdata, char **texture_data)
{
	int	i;

	i = 0;
	while (texture_data[i])
	{
		if (process_texture_line(mapdata, texture_data[i]) != SUCCESS)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
