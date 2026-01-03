/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:19:58 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/12 14:59:12 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	clear_layer(t_img *layer, int layer_size)
{
	ft_memset(layer->addr, 0, layer_size);
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
