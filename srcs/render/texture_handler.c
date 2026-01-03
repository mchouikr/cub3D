/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:46:08 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 17:42:22 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	texture_handler_error(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		if (data->textures[i] == NULL)
		{
			j = 0;
			while (j < 4)
			{
				if (data->textures[j])
					mlx_destroy_image(data->mlx_ptr, data->textures[j]);
				j++;
			}
		}
		i++;
	}
	return (0);
}

static bool	check_textxure_fd(t_mapdata *map, int fd)
{
	fd = open(map->no_txt_path, O_RDONLY);
	if (fd < 0 || check_fd_error(map->no_txt_path, ".xpm", fd))
		return (false);
	close(fd);
	fd = open(map->so_txt_path, O_RDONLY);
	if (fd < 0 || check_fd_error(map->so_txt_path, ".xpm", fd))
		return (false);
	close(fd);
	fd = open(map->we_txt_path, O_RDONLY);
	if (fd < 0 || check_fd_error(map->we_txt_path, ".xpm", fd))
		return (false);
	close(fd);
	fd = open(map->ea_txt_path, O_RDONLY);
	if (fd < 0 || check_fd_error(map->ea_txt_path, ".xpm", fd))
		return (false);
	close(fd);
	return (true);
}

static bool	validate_mapdata(t_mapdata *map)
{
	int	fd;

	fd = 0;
	if (!map)
	{
		ft_fprintf(2, MAPDATA_IS_NULL);
		return (false);
	}
	if (!map->no_txt_path || !map->so_txt_path || !map->ea_txt_path
		|| !map->we_txt_path)
	{
		ft_fprintf(2, NULL_TEXTURE_PATH);
		return (false);
	}
	if (check_textxure_fd(map, fd) == false)
		return (false);
	return (true);
}

int	load_textures_buffer(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!data->textures[i])
			return (1);
		data->textures_buffer[i] = malloc(sizeof(t_img));
		if (!data->textures_buffer[i])
			return (1);
		data->textures_buffer[i]->img = data->textures[i];
		data->textures_buffer[i]->addr = mlx_get_data_addr(data->textures[i],
				&data->textures_buffer[i]->bits_per_pixel,
				&data->textures_buffer[i]->line_length,
				&data->textures_buffer[i]->endian);
		i++;
	}
	return (0);
}

int	load_textures(t_data *data, t_mapdata *map)
{
	int	size;

	if (validate_mapdata(map) == false)
	{
		ft_fprintf(2, INVALID_TEXTURE);
		return (FAILURE);
	}
	size = TILE_SIZE;
	data->textures[NORTH] = mlx_xpm_file_to_image(data->mlx_ptr,
			map->no_txt_path, &size, &size);
	data->textures[SOUTH] = mlx_xpm_file_to_image(data->mlx_ptr,
			map->so_txt_path, &size, &size);
	data->textures[EAST] = mlx_xpm_file_to_image(data->mlx_ptr,
			map->ea_txt_path, &size, &size);
	data->textures[WEST] = mlx_xpm_file_to_image(data->mlx_ptr,
			map->we_txt_path, &size, &size);
	texture_handler_error(data);
	if (load_textures_buffer(data) != 0)
	{
		ft_fprintf(2, FAILED_LOADING_TEXTURES);
		return (FAILURE);
	}
	return (0);
}
