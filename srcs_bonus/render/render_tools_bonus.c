/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:19:58 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/17 23:31:30 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	mlx_put_rectangle_to_layer(t_img *layer, t_rect rect)
{
	char	*dest;
	int		line_bytes;
	int		i;
	int		j;

	if (rect.x < 0 || rect.y < 0 || rect.x + rect.size >= WIN_WIDTH || rect.y
		+ rect.size >= WIN_HEIGHT)
		return ;
	dest = layer->addr + (rect.y * layer->line_length + rect.x
			* (layer->bits_per_pixel / 8));
	line_bytes = rect.size * (layer->bits_per_pixel / 8);
	i = -1;
	while (++i < rect.size + 1)
	{
		j = 0;
		while (j < line_bytes)
		{
			*(unsigned int *)(dest + j) = rect.color;
			j += 4;
		}
		dest += layer->line_length;
	}
}

// void	mlx_put_rectangle_to_layer(t_img *layer, int x, int y, int size,
// 		int color)
// {
// 	char	*dest;
// 	int		line_bytes;
// 	int		i;
// 	int		j;

// 	if (x < 0 || y < 0 || x + size >= WIN_WIDTH || y + size >= WIN_HEIGHT)
// 		return ;
// 	dest = layer->addr + (y * layer->line_length + x * (layer->bits_per_pixel
// 				/ 8));
// 	line_bytes = size * (layer->bits_per_pixel / 8);
// 	i = 0;
// 	while (i < size + 1)
// 	{
// 		j = 0;
// 		while (j < line_bytes)
// 		{
// 			*(unsigned int *)(dest + j) = color;
// 			j += 4;
// 		}
// 		dest += layer->line_length;
// 		i++;
// 	}
// }

void	clear_layer(t_img *layer, int layer_size)
{
	unsigned int	*pixels;
	int				i;

	pixels = (unsigned int *)layer->addr;
	i = 0;
	while (i < layer_size)
	{
		pixels[i] = 0;
		i++;
	}
}

void	put_pixel_to_layer(t_img *layer, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = layer->addr + (y * layer->line_length + x * (layer->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

static void	process_line_error(t_line *line, int *x1, int *y1)
{
	int	e2;

	e2 = 2 * line->err;
	if (e2 > -line->dy)
	{
		line->err -= line->dy;
		*x1 += line->sx;
	}
	if (e2 < line->dx)
	{
		line->err += line->dx;
		*y1 += line->sy;
	}
}

void	draw_line(t_img *layer, t_line line)
{
	int	x1;
	int	y1;

	x1 = line.x1;
	y1 = line.y1;
	line.dx = abs(line.x2 - line.x1);
	line.dy = abs(line.y2 - line.y1);
	if (line.x1 < line.x2)
		line.sx = 1;
	else
		line.sx = -1;
	if (line.y1 < line.y2)
		line.sy = 1;
	else
		line.sy = -1;
	line.err = line.dx - line.dy;
	while (x1 != line.x2 || y1 != line.y2)
	{
		put_pixel_to_layer(layer, x1, y1, line.color);
		process_line_error(&line, &x1, &y1);
	}
}

// void	draw_line(t_img *layer, int x1, int y1, int x2, int y2, int color)
// {
// 	int	dx;
// 	int	dy;
// 	int	sx;
// 	int	sy;
// 	int	err;
// 	int	e2;

// 	dx = abs(x2 - x1);
// 	dy = abs(y2 - y1);
// 	if (x1 < x2)
// 		sx = 1;
// 	else
// 		sx = -1;
// 	if (y1 < y2)
// 		sy = 1;
// 	else
// 		sy = -1;
// 	err = dx - dy;
// 	while (x1 != x2 || y1 != y2)
// 	{
// 		put_pixel_to_layer(layer, x1, y1, color);
// 		e2 = 2 * err;
// 		if (e2 > -dy)
// 		{
// 			err -= dy;
// 			x1 += sx;
// 		}
// 		if (e2 < dx)
// 		{
// 			err += dx;
// 			y1 += sy;
// 		}
// 	}
// }
