/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:54:05 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 17:43:57 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_file_format(char *str, char *format)
{
	int		len;
	char	*b_name;

	if (!str)
		return (1);
	b_name = ft_strrchr(str, '/');
	if (b_name)
		b_name++;
	else
		b_name = str;
	len = ft_strlen(b_name);
	if (b_name[0] == '.' && len == 4 && ft_strncmp(b_name, format, 4) == 0)
	{
		ft_fprintf(2, INVALID_FILE);
		return (FAILURE);
	}
	if (len < 4 || ft_strncmp(&b_name[len - 4], format, 4) != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	check_fd_format(char *str, char *format, int fd)
{
	int		len;
	char	*b_name;

	if (!str)
		return (1);
	b_name = ft_strrchr(str, '/');
	if (b_name)
		b_name++;
	else
		b_name = str;
	len = ft_strlen(b_name);
	if (b_name[0] == '.' && len == 4 && ft_strncmp(b_name, format, 4) == 0)
	{
		ft_fprintf(2, INVALID_FILE);
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (len < 4 || ft_strncmp(&b_name[len - 4], format, 4) != 0)
		return (1);
	return (0);
}

int	check_fd_error(char *str, char *format, int fd)
{
	if (fd == -1)
	{
		ft_fprintf(2, CANNOT_OPEN_FILE);
		exit(EXIT_FAILURE);
	}
	if (check_fd_format(str, format, fd))
	{
		ft_fprintf(2, CANNOT_OPEN_FILE);
		close(fd);
		exit(EXIT_FAILURE);
	}
	return (0);
}

char	*reading_map(char *read_map, char *tmp, char *oneline_file, int fd)
{
	int	line_count;

	line_count = 0;
	while (1)
	{
		read_map = get_next_line(fd);
		if (read_map == NULL)
			break ;
		if (ft_strlen(read_map) == 0)
			return (ft_fprintf(2, EMPTY_FILE), free(oneline_file),
				free(read_map), close(fd), NULL);
		tmp = oneline_file;
		oneline_file = ft_strjoin(oneline_file, read_map);
		free(tmp);
		free(read_map);
		if (!oneline_file)
			return (free(oneline_file), close(fd), NULL);
		line_count++;
	}
	if (line_count < 4)
		return (ft_fprintf(2, "Error\nInvalid file\n"), free(oneline_file),
			free(read_map), close(fd), NULL);
	return (oneline_file);
}

bool	check_virgules(char *values)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (values[i])
	{
		if (values[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (FAILURE);
	return (SUCCESS);
}
