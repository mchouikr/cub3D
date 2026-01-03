/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_handler_helper2_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:02:36 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 13:25:34 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	free_sprite_buffers(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 5 && data->text_sprite_buffer[i])
	{
		if (data->text_sprite_buffer[i])
		{
			free(data->text_sprite_buffer[i]);
			data->text_sprite_buffer[i] = NULL;
		}
	}
}

void	free_sprite_images(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 5 && data->textures_sprites[i])
	{
		if (data->textures_sprites[i] && data->mlx_ptr)
		{
			mlx_destroy_image(data->mlx_ptr, data->textures_sprites[i]);
			data->textures_sprites[i] = NULL;
		}
	}
}

void	free_sprite_resources(t_data *data)
{
	if (!data || !data->sprite)
		return ;
	if (data->sprite->zbuffer != NULL)
	{
		free(data->sprite->zbuffer);
		data->sprite->zbuffer = NULL;
	}
	if (data->sprite->order != NULL)
	{
		free(data->sprite->order);
		data->sprite->order = NULL;
	}
	if (data->sprite->distance != NULL)
	{
		free(data->sprite->distance);
		data->sprite->distance = NULL;
	}
	free_sprite_images(data);
	free_sprite_buffers(data);
	free(data->sprite);
	data->sprite = NULL;
}

void	free_texture_images(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 5 && data->textures[i])
	{
		if (data->textures[i])
		{
			mlx_destroy_image(data->mlx_ptr, data->textures[i]);
			data->textures[i] = NULL;
		}
	}
}

void	free_texture_buffers(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 5 && data->textures_buffer[i])
	{
		if (data->textures_buffer[i])
		{
			free(data->textures_buffer[i]);
			data->textures_buffer[i] = NULL;
		}
	}
}
