/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:06:49 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 01:39:48 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	update_frame_counter(t_data *data)
{
	static double	last_update = 0;
	struct timeval	current_time;
	double			current_timestamp;

	gettimeofday(&current_time, NULL);
	current_timestamp = current_time.tv_sec + (current_time.tv_usec
			/ 1000000.0);
	if (current_timestamp - last_update >= 0.1)
	{
		data->sprite->frame = (data->sprite->frame + 1) % 5;
		data->sprite->frame_count = 0;
		last_update = current_timestamp;
	}
}

void	update_sprite_positions(t_data *data)
{
	int		count;
	int		y;
	int		x;
	double	dx;
	double	dy;

	count = 0;
	y = -1;
	while (data->mapdata->map[++y])
	{
		x = 0;
		while (data->mapdata->map[y][x])
		{
			if (data->mapdata->map[y][x] == 'C')
			{
				data->sprite->order[count] = y * data->mapdata->width + x;
				dx = (x + 0.5) - data->player->x_pos;
				dy = (y + 0.5) - data->player->y_pos;
				data->sprite->distance[count] = dx * dx + dy * dy;
				count++;
			}
			x++;
		}
	}
	data->sprite->num_sprites = count;
}

int	calculate_tex_x(t_sprite_calc *sp, int stripe)
{
	int	tex_x;

	tex_x = (int)(256 * (stripe - (-sp->width / 2 + sp->screen_x)) * SPRITE_SIZE
			/ sp->width) / 256;
	return (fmin(fmax(tex_x, 0), SPRITE_SIZE - 1));
}

void	sort_sprites(t_data *data)
{
	int		i;
	int		j;
	double	temp_dist;
	int		temp_order;

	i = 0;
	while (i < data->sprite->num_sprites - 1)
	{
		j = 0;
		while (j < data->sprite->num_sprites - i - 1)
		{
			if (data->sprite->distance[j] < data->sprite->distance[j + 1])
			{
				temp_dist = data->sprite->distance[j];
				data->sprite->distance[j] = data->sprite->distance[j + 1];
				data->sprite->distance[j + 1] = temp_dist;
				temp_order = data->sprite->order[j];
				data->sprite->order[j] = data->sprite->order[j + 1];
				data->sprite->order[j + 1] = temp_order;
			}
			j++;
		}
		i++;
	}
}

void	draw_sprite_line(t_data *data, t_sprite_calc *sp, int stripe)
{
	int				y;
	int				d;
	int				tex_y;
	char			*sprite_pixel;
	unsigned int	color;

	y = sp->draw_start_y - 1;
	while (++y < sp->draw_end_y)
	{
		d = y * 256 - WIN_HEIGHT * 128 + sp->height * 128;
		tex_y = ((d * SPRITE_SIZE) / sp->height) / 256;
		tex_y = fmin(fmax(tex_y, 0), SPRITE_SIZE - 1);
		sprite_pixel = sp->current_sprite->addr + (tex_y
				* sp->current_sprite->line_length + sp->tex_x
				* (sp->current_sprite->bits_per_pixel / 8));
		color = *(unsigned int *)sprite_pixel;
		if (color != 0xFF000000)
			put_pixel_to_layer(data->sprite_layer, stripe, y, color);
	}
}

// void	draw_sprite_stripes(t_data *data, double transform_y, int sprite_wwidth,
// 		int sprite_screen_x, int draw_start_x, int draw_end_x, int draw_start_y,
// 		int draw_end_y)
// {
// 	static int		frame = 0;
// 	int				stripe;
// 	int				y;
// 	int				tex_x;
// 	t_img			*current_sprite;
// 	int				d;
// 	int				tex_y;
// 	char			*sprite_pixel;
// 	unsigned int	color;
// 	static int		frame_count = 0;

// 	tex_x = 0;
// 	current_sprite = data->text_sprite_buffer[frame];
// 	stripe = draw_start_x;
// 	while (stripe < draw_end_x)
// 	{
// 		if (transform_y > 0 && stripe >= 0 && stripe < WIN_WIDTH
// 			&& transform_y < data->sprite->zbuffer[stripe])
// 		{
// 			tex_x = (int)(256 * (stripe - (-sprite_wwidth / 2
// 							+ sprite_screen_x)) * SPRITE_SIZE / sprite_wwidth)
// 				/ 256;
// 			tex_x = fmin(fmax(tex_x, 0), SPRITE_SIZE - 1);
// 			for (y = draw_start_y; y < draw_end_y; y++)
// 			{
// 				d = (y)*256 - WIN_HEIGHT * 128 + (draw_end_y - draw_start_y)
// 					* 128;
// 				tex_y = ((d * SPRITE_SIZE) / (draw_end_y - draw_start_y)) / 256;
// 				tex_y = fmin(fmax(tex_y, 0), SPRITE_SIZE - 1);
// 				sprite_pixel = current_sprite->addr + (tex_y
// 						* current_sprite->line_length + tex_x
// 						* (current_sprite->bits_per_pixel / 8));
// 				color = *(unsigned int *)sprite_pixel;
// 				if (color != 0xFF000000)
// 					put_pixel_to_layer(data->sprite_layer, stripe, y, color);
// 			}
// 		}
// 		stripe++;
// 	}
// 	if (frame_count++ >= 10)
// 	{
// 		frame = (frame + 1) % 5;
// 		frame_count = 0;
// 	}
// }

// void	update_sprite_positions(t_data *data)
// {
// 	int		count;
// 	double	dx;
// 	double	dy;

// 	count = 0;
// 	int y, x;
// 	for (y = 0; data->mapdata->map[y]; y++)
// 	{
// 		for (x = 0; data->mapdata->map[y][x]; x++)
// 		{
// 			if (data->mapdata->map[y][x] == 'C')
// 			{
// 				data->sprite->order[count] = y * data->mapdata->width
// 					+ x;
// 				dx = (x + 0.5) - data->player->x_pos;
// 				dy = (y + 0.5) - data->player->y_pos;
// 				data->sprite->distance[count] = dx * dx + dy * dy;
// 				count++;
// 			}
// 		}
// 	}
// 	data->sprite->num_sprites = count;
// }

// void	draw_sprites(t_data *data)
// {
// 	int	i;
// 	int	sprite_map_pos;
// 	int	sprite_y;
// 	int	sprite_x;
// 	int	sprite_screen_x;
// 	int	sprite_height;
// 	int	draw_start_y;
// 	int	draw_end_y;
// 	int	sprite_width;
// 	int	draw_start_x;
// 	int	draw_end_x;

// 	double sprite_x2, sprite_y2, inv_det;
// 	double transform_x, transform_y;
// 	update_sprite_positions(data);
// 	if (!data || !data->sprite || !data->mapdata || !data->mapdata->map)
// 		return ;
// 	sort_sprites(data);
// 	i = 0;
// 	while (i < data->sprite->num_sprites)
// 	{
// 		sprite_map_pos = data->sprite->order[i];
// 		sprite_y = sprite_map_pos / data->mapdata->width;
// 		sprite_x = sprite_map_pos % data->mapdata->width;
// 		sprite_x2 = (sprite_x + 0.5) - data->player->x_pos;
// 		sprite_y2 = (sprite_y + 0.5) - data->player->y_pos;
// 		inv_det = 1.0 / (data->camera->plane_x * data->camera->dir_y
// 				- data->camera->dir_x * data->camera->plane_y);
// 		transform_x = inv_det * (data->camera->dir_y * sprite_x2
// 				- data->camera->dir_x * sprite_y2);
// 		transform_y = inv_det * (-data->camera->plane_y * sprite_x2
// 				+ data->camera->plane_x * sprite_y2);
// 		sprite_screen_x = (int)((WIN_WIDTH / 2) * (1 + transform_x
// / transform_y));
// 		sprite_height = abs((int)(WIN_HEIGHT / transform_y / 3));
// 		draw_start_y = -sprite_height / 2 + WIN_HEIGHT / 2;
// 		if (draw_start_y < 0)
// 			draw_start_y = 0;
// 		draw_end_y = sprite_height / 2 + WIN_HEIGHT / 2;
// 		if (draw_end_y >= WIN_HEIGHT)
// 			draw_end_y = WIN_HEIGHT - 1;
// 		sprite_width = abs((int)(WIN_HEIGHT / transform_y / 3));
// 		draw_start_x = -sprite_width / 2 + sprite_screen_x;
// 		if (draw_start_x < 0)
// 			draw_start_x = 0;
// 		draw_end_x = sprite_width / 2 + sprite_screen_x;
// 		if (draw_end_x >= WIN_WIDTH)
// 			draw_end_x = WIN_WIDTH - 1;
// 		draw_sprite_stripes(data, transform_y, sprite_width, sprite_screen_x,
// 			draw_start_x, draw_end_x, draw_start_y, draw_end_y);
// 		i++;
// 	}
// }

// void	draw_sprites(t_data *data)
// {
// 	int	i;
// 	int	sprite_map_pos;
// 	int	sprite_y;
// 	int	sprite_x;
// 	int	spriteScreenX;
// 	int	spriteHeight;
// 	int	drawStartY;
// 	int	drawEndY;
// 	int	spriteWidth;
// 	int	drawStartX;
// 	int	drawEndX;

// 	double spriteX, spriteY, invDet;
// 	double transformX, transformY;
// 	update_sprite_positions(data);
// 	// printf("Drawing sprites, count: %d\n", data->sprite->num_sprites);
// 	// Basic validation
// 	if (!data || !data->sprite || !data->mapdata || !data->mapdata->map)
// 		return ;
// 	sort_sprites(data);
// 	// Draw each sprite
// 	for (i = 0; i < data->sprite->num_sprites; i++)
// 	{
// 		sprite_map_pos = data->sprite->order[i];
// 		sprite_y = sprite_map_pos / data->mapdata->width;
// 		sprite_x = sprite_map_pos % data->mapdata->width;
// 		spriteX = (sprite_x + 0.5) - data->player->x_pos;
// 		spriteY = (sprite_y + 0.5) - data->player->y_pos;
// 		// Transform sprite with the inverse camera matrix
// 		invDet = 1.0 / (data->camera->plane_x * data->camera->dir_y
// 				- data->camera->dir_x * data->camera->plane_y);
// 		transformX = invDet * (data->camera->dir_y * spriteX
// 				- data->camera->dir_x * spriteY);
// 		transformY = invDet * (-data->camera->plane_y * spriteX
// 				+ data->camera->plane_x * spriteY);
// 		spriteScreenX = (int)((WIN_WIDTH / 2) * (1 + transformX / transformY));
// 		spriteHeight = abs((int)(WIN_HEIGHT / transformY / 3));
// 		drawStartY = -spriteHeight / 2 + WIN_HEIGHT / 2;
// 		if (drawStartY < 0)
// 			drawStartY = 0;
// 		drawEndY = spriteHeight / 2 + WIN_HEIGHT / 2;
// 		if (drawEndY >= WIN_HEIGHT)
// 			drawEndY = WIN_HEIGHT - 1;
// 		spriteWidth = abs((int)(WIN_HEIGHT / transformY / 3));
// 		drawStartX = -spriteWidth / 2 + spriteScreenX;
// 		if (drawStartX < 0)
// 			drawStartX = 0;
// 		drawEndX = spriteWidth / 2 + spriteScreenX;
// 		if (drawEndX >= WIN_WIDTH)
// 			drawEndX = WIN_WIDTH - 1;
// 		// Draw the sprite
// 		draw_sprite_stripes(data, transformY, spriteWidth, spriteScreenX,
// 			drawStartX, drawEndX, drawStartY, drawEndY);
// 	}
// }

// void draw_sprite_stripes(t_data *data, double transform_y, int sprite_wwidth,
//                         int sprite_screen_x, int draw_start_x,
// int draw_end_x,
//                         int draw_start_y, int draw_end_y)
// {
//     static int frame = 0;
//     int stripe;
//     int y;
// 	int tex_x = 0;

//     // Use animated sprite frames
//     t_img *current_sprite = data->text_sprite_buffer[frame];
//    // const int SPRITE_SIZE = 32; // Sprite texture size is 32x32
//     // Draw each vertical stripe of the sprite
// 	stripe = draw_start_x;
//     while (stripe < draw_end_x)
//     {
//         // Only draw if the sprite is in front of the wall at this x position
//         if (transform_y > 0 && stripe >= 0 && stripe < WIN_WIDTH &&
//             transform_y < data->sprite->zbuffer[stripe])
//         {
// 			// printf("Stripe %d: transform_y = %f, zbuffer = %f\n",
//             //    stripe, transform_y, data->sprite->zbuffer[stripe]);
//             // Calculate texture X coordinate for sprite
//             tex_x = (int)(256 * (stripe - (-sprite_wwidth / 2
// + sprite_screen_x))
//                             * SPRITE_SIZE / sprite_wwidth) / 256;

//             // Bounds check for texture coordinates
//             tex_x = fmin(fmax(tex_x, 0), SPRITE_SIZE - 1);

//             // Draw vertical line for sprite
//             for (y = draw_start_y; y < draw_end_y; y++)
//             {
//                 // Calculate Y coordinate in texture
//                 int d = (y) * 256 - WIN_HEIGHT * 128 +
//                         (draw_end_y - draw_start_y) * 128;
//                 int tex_y = ((d * SPRITE_SIZE) / (draw_end_y - draw_start_y))
// / 256;

//                 tex_y = fmin(fmax(tex_y, 0), SPRITE_SIZE - 1);

//                 // Get pixel from sprite texture
//                 char *sprite_pixel = current_sprite->addr +
//                     (tex_y * current_sprite->line_length +
//                      tex_x * (current_sprite->bits_per_pixel / 8));

//                 // Draw pixel if not transparent
// 			unsigned int color = *(unsigned int *)sprite_pixel;
// 			if(color != 0xFF000000)
// 				put_pixel_to_layer(data->sprite_layer, stripe, y, color);
//             }
//         }
// 		stripe++;
//     }

//     // Animate sprite
//     static int frame_count = 0;
//     if (frame_count++ >= 10)
//     {
//         frame = (frame + 1) % 5;
//         frame_count = 0;
//     }
// }