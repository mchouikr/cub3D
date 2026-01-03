/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:50:32 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 15:39:30 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	load_textures_sprite(t_data *data)
{
	int	size;

	size = 32;
	data->textures_sprites[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/sprite/coin1.xpm", &size, &size);
	if (!data->textures_sprites[0])
		return (1);
	data->textures_sprites[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/sprite/coin2.xpm", &size, &size);
	if (!data->textures_sprites[1])
		return (1);
	data->textures_sprites[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/sprite/coin3.xpm", &size, &size);
	if (!data->textures_sprites[2])
		return (1);
	data->textures_sprites[3] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/sprite/coin4.xpm", &size, &size);
	if (!data->textures_sprites[3])
		return (1);
	data->textures_sprites[4] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/sprite/coin5.xpm", &size, &size);
	if (!data->textures_sprites[4])
		return (1);
	return (0);
}

int	fill_sprite_buffer(t_data *data, int i)
{
	if (!data->textures_sprites[i])
	{
		printf("Texture sprite %d is NULL\n", i);
		return (1);
	}
	data->text_sprite_buffer[i] = malloc(sizeof(t_img));
	if (!data->text_sprite_buffer[i])
	{
		printf("Failed to allocate memory for text_sprite_buffer[%d]\n", i);
		return (1);
	}
	data->text_sprite_buffer[i]->img = data->textures_sprites[i];
	data->text_sprite_buffer[i]->addr = mlx_get_data_addr(
			data->textures_sprites[i],
			&data->text_sprite_buffer[i]->bits_per_pixel,
			&data->text_sprite_buffer[i]->line_length,
			&data->text_sprite_buffer[i]->endian);
	return (0);
}

int	load_sprite_buffer(t_data *data)
{
	int	i;

	i = 0;
	if (load_textures_sprite(data))
	{
		printf("Error\nFailed to load textures\n");
		on_destroy(data);
		exit (1);
	}
	while (i < 5)
	{
		if (fill_sprite_buffer(data, i) != 0)
			return (1);
		i++;
	}
	return (0);
}

// void	animate_sprites(t_data *data)
// {
//     static int	frame = 0;
//     static int	frame_count = 0;
//     int			x;
//     int			y;

//     if (frame_count++ >= 10)
//     {
//         frame = (frame + 1) % 5; // Assuming 5 frames
//         frame_count = 0;
//     }
//     mlx_clear_window(data->mlx_ptr, data->win_ptr);
//     if (data->text_sprite_buffer[frame]
// 	&& data->text_sprite_buffer[frame]->img)
// //     {
// //         x = 100;
// //         y = 100;
// //         mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
// 	data->text_sprite_buffer[frame]->img, x, y);
//     }
//     else
//     {
//         printf("Frame %d is NULL or has no image\n", frame);
//     }
// }

// void	animate_sprite_at(t_data *data, int tile_x, int tile_y)
// {
//     static int	frame = 0;

//     // Calculate screen coordinates based on TILE_SIZE
//     int x = tile_x * TILE_SIZE;
//     int y = tile_y * TILE_SIZE;

//     if (data->text_sprite_buffer[frame]
	// && data->text_sprite_buffer[frame]->img)
//         mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
//             data->text_sprite_buffer[frame]->img, x, y);

//     // Increment the frame counter (wrap around as needed)
//     frame = (frame + 1) % 5;
// }
