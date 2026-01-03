/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:59:14 by edelplan          #+#    #+#             */
/*   Updated: 2024/08/27 12:36:58 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_int(char *str, char c)
{
	int	i;

	c = '\n';
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

//we read until \n or until end of file
char	*ft_read_line(int fd, char *buff, char *stash)
{
	ssize_t		b_read;
	char		*line;
	char		*tmp;

	line = stash;
	b_read = read(fd, buff, BUFFER_SIZE);
	while (b_read > 0)
	{
		buff[b_read] = '\0';
		if (!line)
			line = ft_strdup(buff);
		else
		{
			tmp = line;
			line = ft_strjoin(tmp, buff);
			free(tmp);
			if (!line)
				return (free(buff), NULL);
		}
		if (ft_strchr_int(line, '\n'))
			return (free(buff), line);
		b_read = read(fd, buff, BUFFER_SIZE);
	}
	return (free(buff), line);
}

//null terminated the line after \n and returns the rest of the line
char	*ft_separate_line(char *line)
{
	int		i;
	char	*remainder;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (0);
	remainder = ft_strdup(line + i + 1);
	if (!remainder)
		return (NULL);
	if (remainder[0] == '\0')
		return (free(remainder), remainder = NULL, NULL);
	line[i + 1] = '\0';
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	line = ft_read_line(fd, buff, stash[fd]);
	if (!line)
		return (NULL);
	stash[fd] = ft_separate_line(line);
	buff = ft_strdup(line);
	return (free (line), buff);
}

//Lit les 3 premieres lignes de 3 fichiers.
//Puis les 3 lignes suivantes des 3 fichiers.
// int	main(int ac, char **argv)
// {
// 	int			fd;
// 	int			fd2;
// 	int			fd3;
// 	char		*gnl;
// 	int			count;

// 	count = 0;
// 	fd = open(argv[1], O_RDONLY);
// 	fd2 = open(argv[2], O_RDONLY);
// 	fd3 = open(argv[3], O_RDONLY);
// 	gnl = NULL;
// 	if (ac == 4)
// 	{
// 		gnl = get_next_line(fd);
// 		printf("[%d]:%s", count, gnl);
// 		free(gnl);
// 		gnl = get_next_line(fd2);
// 		printf("[%d]:%s", count, gnl);
// 		free(gnl);
// 		gnl = get_next_line(fd3);
// 		printf("[%d]:%s", count, gnl);
// 		free(gnl);
// 		gnl = get_next_line(fd);
// 		printf("[%d]:%s", count, gnl);
// 		free(gnl);
// 		gnl = get_next_line(fd2);
// 		printf("[%d]:%s", count, gnl);
// 		free(gnl);
// 		gnl = get_next_line(fd3);
// 		printf("[%d]:%s", count, gnl);
// 		free(gnl);

// 	}
// 	else
// 		printf("error");
// 	if (gnl == NULL)
// 		free(gnl);
// 	return (close(fd), close(fd2), close(fd3), 0);
// }
