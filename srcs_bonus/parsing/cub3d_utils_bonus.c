/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:40:38 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 00:40:56 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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

// void	mlx_put_rectangle(t_data *data, int x, int y, int size, int color)
// 	{
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;

// 	img = mlx_new_image(data->mlx_ptr, size, size);
// 	addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
// 	for (int i = 0; i < size; i++)
// 	{
// 		for (int j = 0; j < size; j++)
// 		{
// 			int pixel = (i * line_length + j * (bits_per_pixel / 8));
// 			*(unsigned int *)(addr + pixel) = color;
// 		}
// 	}
// 	//mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, x, y);
// 	//mlx_destroy_image(data->mlx_ptr, img);
// }