/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:02:23 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/17 23:32:03 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	draw_coin_texture(t_data *data, t_img *sprite, int pos[2], float ts)
{
	t_tex_coord	tex;
	int			draw[2];

	tex.y = 0;
	while (tex.y < SPRITE_SIZE)
	{
		tex.x = 0;
		while (tex.x < SPRITE_SIZE)
		{
			tex.pixel = sprite->addr + (tex.y * sprite->line_length + tex.x
					* (sprite->bits_per_pixel / 8));
			draw[0] = pos[0] - (ts / 4) + (tex.x * ts / (2 * SPRITE_SIZE));
			draw[1] = pos[1] - (ts / 4) + (tex.y * ts / (2 * SPRITE_SIZE));
			if (*(unsigned int *)tex.pixel != 0xFF000000)
				put_pixel_to_layer(data->map_layer, draw[0], draw[1],
					*(unsigned int *)tex.pixel);
			tex.x++;
		}
		tex.y++;
	}
}

void	draw_minimap_static(t_data *data, t_mapdata *mapdata, int x_pos,
		int y_pos)
{
	t_rect	rect;
	int		x;
	int		y;

	y = 0;
	if (!mapdata || !mapdata->map)
		return ;
	while (mapdata->map[y])
	{
		x = 0;
		while (mapdata->map[y][x])
		{
			rect.x = x_pos + (x * TILE_SIZE * MINIMAP_SCALE);
			rect.y = y_pos + (y * TILE_SIZE * MINIMAP_SCALE);
			rect.size = TILE_SIZE * MINIMAP_SCALE;
			if (mapdata->map[y][x] == '1')
				rect.color = 0x808080;
			else
				rect.color = 0;
			mlx_put_rectangle_to_layer(data->map_layer, rect);
			x++;
		}
		y++;
	}
}

void	draw_minimap_border(t_data *d, int b_x, int b_y, int size)
{
	t_rect	rect;
	t_line	line;

	rect = (t_rect){b_x, b_y, size, convert_to_hex(d->mapdata->c_rgb)};
	mlx_put_rectangle_to_layer(d->map_layer, rect);
	line = (t_line){
		b_x, b_y, b_x + size,
		b_y,
		0xFFFFFF,
		size,
		0,
		1,
		0,
		0
	};
	draw_line(d->map_layer, line);
	line = (t_line){b_x, b_y + size, b_x + size, b_y + size, 0xFFFFFF, size, 0,
		1, 0, 0};
	draw_line(d->map_layer, line);
	line = (t_line){b_x, b_y, b_x, b_y + size, 0xFFFFFF, 0, size, 0, 1, 0};
	draw_line(d->map_layer, line);
	line = (t_line){b_x + size, b_y, b_x + size, b_y + size, 0xFFFFFF, 0, size,
		0, 1, 0};
	draw_line(d->map_layer, line);
}

void	draw_coins(t_data *data, int pos_x, int pos_y, float tile_size)
{
	t_img	*current_sprite;
	int		pos[2];
	t_rect	rect;

	current_sprite = data->text_sprite_buffer[data->sprite->frame];
	if (!current_sprite || !current_sprite->img)
	{
		rect = (t_rect){pos_x - tile_size / 4, pos_y - tile_size / 4, tile_size
			/ 2, 0xFFFF00};
		mlx_put_rectangle_to_layer(data->map_layer, rect);
		return ;
	}
	pos[0] = pos_x;
	pos[1] = pos_y;
	draw_coin_texture(data, current_sprite, pos, tile_size);
}

// void	draw_ray_hit(t_data *data)
// {
// 	int				player_screen_x;
// 	int				player_screen_y;
// 	int				map_size;
// 	float			tile_size;
// 	int				border_size;
// 	int				border_x;
// 	int				border_y;
// 	int				start_x;
// 	int				start_y;
// 	int				end_x;
// 	int				end_y;
// 	double			player_screen_pos_x;
// 	double			player_screen_pos_y;
// 	static int		frame = 0;
// 	static int		frame_count = 0;
// 	float			slide_offset;
// 	bool			is_vertical;
// 	t_img			*current_sprite;
// 	char			*sprite_pixel;
// 	int				draw_x;
// 	int				draw_y;
// 	unsigned int	color;

// 	int x, y;
// 	int pos_x, pos_y;
// 	player_screen_x = 100;
// 	player_screen_y = 100;
// 	map_size = 12;
// 	tile_size = TILE_SIZE * MINIMAP_SCALE;
// 	border_size = map_size * tile_size;
// 	border_x = player_screen_x - border_size / 2;
// 	border_y = player_screen_y - border_size / 2;
// 	clear_layer(data->map_layer, WIN_HEIGHT * WIN_WIDTH);
// 	clear_layer(data->ray_layer, WIN_HEIGHT * WIN_WIDTH);
// 	mlx_put_rectangle_to_layer(data->map_layer, border_x, border_y, border_size,
// 		convert_to_hex(data->mapdata->c_rgb));
// 	draw_line(data->map_layer, border_x, border_y, border_x + border_size,
// 		border_y, 0xFFFFFF);
// 	// Bottom line
// 	draw_line(data->map_layer, border_x, border_y + border_size, border_x
// 		+ border_size, border_y + border_size, 0xFFFFFF);
// 	// Left line
// 	draw_line(data->map_layer, border_x, border_y, border_x, border_y
// 		+ border_size, 0xFFFFFF);
// 	// Right line
// 	draw_line(data->map_layer, border_x + border_size, border_y, border_x
// 		+ border_size, border_y + border_size, 0xFFFFFF);
// 	// Calculate bounds for visible map section
// 	start_x = (int)data->player->x_pos - map_size / 2;
// 	start_y = (int)data->player->y_pos - map_size / 2;
// 	end_x = start_x + map_size;
// 	end_y = start_y + map_size;
// 	// Clamp bounds to map edges
// 	start_x = fmax(0, start_x);
// 	start_y = fmax(0, start_y);
// 	end_x = fmin(end_x, data->mapdata->width);
// 	end_y = fmin(end_y, data->mapdata->height);
// 	player_screen_pos_x = player_screen_x + tile_size / 2;
// 	player_screen_pos_y = player_screen_y + tile_size / 2;
// 	// Update animation frame globally
// 	if (frame_count++ >= 10) // Same speed as animate_sprites
// 	{
// 		frame = (frame + 1) % 5; // 5 frames like animate_sprites
// 		frame_count = 0;
// 	}
// 	// Draw visible map tiles
// 	for (y = start_y; y < end_y; y++)
// 	{
// 		for (x = start_x; x < end_x; x++)
// 		{
// 			if (x < 0 || y < 0 || x >= data->mapdata->width
// 				|| y >= data->mapdata->height)
// 				continue ;
// 			// Calculate tile positions relative to player
// 			pos_x = player_screen_pos_x + ((x - data->player->x_pos)
// 					* tile_size);
// 			pos_y = player_screen_pos_y + ((y - data->player->y_pos)
// 					* tile_size);
// 			if (pos_x - tile_size / 2 < border_x || pos_x + tile_size
// 				/ 2 > border_x + border_size || pos_y - tile_size / 2 < border_y
// 				|| pos_y + tile_size / 2 > border_y + border_size)
// 				continue ;
// 			// Draw tiles centered on their positions
// 			if (data->mapdata->map[y][x] == '1')
// 			{
// 				mlx_put_rectangle_to_layer(data->map_layer, pos_x - tile_size
// 					/ 2, pos_y - tile_size / 2, tile_size,
// 					convert_to_hex(data->mapdata->f_rgb));
// 			}
// 			else if (data->mapdata->map[y][x] == 'D')
// 			{
// 				// Draw door using lines based on orientation
// 				if (data->mapdata->door_states[y][x] == OPENING
// 					|| data->mapdata->door_states[y][x] == CLOSING)
// 				{
// 					slide_offset = data->mapdata->door_timers[y][x];
// 					if (data->mapdata->door_states[y][x] == CLOSING)
// 						slide_offset = 1.0 - slide_offset;
// 					// Check door orientation by looking at adjacent walls
// 					is_vertical = (x > 0 && data->mapdata->map[y][x - 1] == '1')
// 						|| (x < data->mapdata->width - 1
// 							&& data->mapdata->map[y][x + 1] == '1');
// 					if (is_vertical)
// 					{
// 						// Vertical door (East-West walls)
// 						draw_line(data->map_layer, pos_x - tile_size / 2
// 							+ (slide_offset * tile_size), pos_y - tile_size / 2,
// 							pos_x - tile_size / 2 + (slide_offset * tile_size),
// 							pos_y + tile_size / 2, 0xAAAAAA);
// 					}
// 					else
// 					{
// 						// Horizontal door (North-South walls)
// 						draw_line(data->map_layer, pos_x - tile_size / 2, pos_y
// 							- tile_size / 2 + (slide_offset * tile_size), pos_x
// 							+ tile_size / 2, pos_y - tile_size / 2
// 							+ (slide_offset * tile_size), 0xAAAAAA);
// 					}
// 				}
// 				else if (data->mapdata->door_states[y][x] == CLOSED)
// 				{
// 					// Same orientation check for closed doors
// 					is_vertical = (x > 0 && data->mapdata->map[y][x - 1] == '1')
// 						|| (x < data->mapdata->width - 1
// 							&& data->mapdata->map[y][x + 1] == '1');
// 					if (!is_vertical)
// 					{
// 						draw_line(data->map_layer, pos_x - tile_size / 2, pos_y
// 							- tile_size / 2, pos_x - tile_size / 2, pos_y
// 							+ tile_size / 2, 0xAAAAAA);
// 					}
// 					else
// 					{
// 						draw_line(data->map_layer, pos_x - tile_size / 2, pos_y
// 							- tile_size / 2, pos_x + tile_size / 2, pos_y
// 							- tile_size / 2, 0xAAAAAA);
// 					}
// 				}
// 			}
// 			else if (data->mapdata->map[y][x] == 'C')
// 			{
// 				current_sprite = data->text_sprite_buffer[frame];
// 				if (current_sprite && current_sprite->img)
// 				{
// 					// Calculate sprite dimensions
// 					int sprite_size = tile_size / 2;
// 						// Make sprite smaller than tile
// 					for (int texY = 0; texY < SPRITE_SIZE; texY++)
// 					{
// 						for (int texX = 0; texX < SPRITE_SIZE; texX++)
// 						{
// 							// Get pixel from sprite texture
// 							sprite_pixel = current_sprite->addr + (texY
// 									* current_sprite->line_length + texX
// 									* (current_sprite->bits_per_pixel / 8));
// 							// Calculate position on minimap
// 							draw_x = pos_x - sprite_size / 2 + (texX
// 									* sprite_size / SPRITE_SIZE);
// 							draw_y = pos_y - sprite_size / 2 + (texY
// 									* sprite_size / SPRITE_SIZE);
// 							// Draw pixel if not transparent
// 							color = *(unsigned int *)sprite_pixel;
// 							if (color != 0xFF000000)
// 							{
// 								put_pixel_to_layer(data->map_layer, draw_x,
// 									draw_y, color);
// 							}
// 						}
// 					}
// 				}
// 				else
// 				{
// 					// Fallback rectangle if sprite isn't loaded
// 					mlx_put_rectangle_to_layer(data->map_layer, pos_x
// 						- tile_size / 4, pos_y - tile_size / 4, tile_size / 2,
// 						0xFFFF00);
// 				}
// 			}
// 		}
// 	}
// 	// Draw rays with same scaling as tiles
// 	double ray_start_x, ray_start_y, ray_end_x, ray_end_y;
// 	for (int i = 0; i < NUM_RAYS; i++)
// 	{
// 		ray_start_x = player_screen_x + 1;
// 		ray_start_y = player_screen_y;
// 		ray_end_x = player_screen_x + (data->rays[i].wall_hit_x * tile_size);
// 		ray_end_y = player_screen_y + (data->rays[i].wall_hit_y * tile_size);
// 		draw_line(data->ray_layer, (int)ray_start_x, (int)ray_start_y,
// 			(int)ray_end_x, (int)ray_end_y, 0xFFFF01);
// 	}
// 	// Draw player
// 	mlx_put_rectangle_to_layer(data->ray_layer, player_screen_x - (PLAYER_SIZE
// 			* MINIMAP_SCALE) / 2, player_screen_y - (PLAYER_SIZE
// 			* MINIMAP_SCALE) / 2, PLAYER_SIZE * MINIMAP_SCALE, 0xFF0000);
// }

// void	draw_minimap_player(t_data *data)
// {
// 	int	layer_size;

// 	layer_size = ((PLAYER_SIZE) * (PLAYER_SIZE))
// 		* (data->player_layer->bits_per_pixel / 8);
// 	clear_layer(data->player_layer, layer_size);
// 	mlx_put_rectangle_to_layer(data->player_layer, 0, 0, PLAYER_SIZE, 0x39FF14);
// }

// void	draw_ray_hit(t_data *data)
// {
// 	int				player_screen_x;
// 	int				player_screen_y;
// 	int				map_size;
// 	float			tile_size;
// 	int				border_size;
// 	int				border_x;
// 	int				border_y;
// 	int				start_x;
// 	int				start_y;
// 	int				end_x;
// 	int				end_y;
// 	double			player_screen_pos_x;
// 	double			player_screen_pos_y;
// 	static int		frame = 0;
// 	static int		frame_count = 0;
// 	float			slide_offset;
// 	bool			is_vertical;
// 	t_img			*current_sprite;
// 	char			*sprite_pixel;
// 	int				draw_x;
// 	int				draw_y;
// 	unsigned int	color;

// 	int x, y;
// 	int pos_x, pos_y;
// 	player_screen_x = 100;
// 	player_screen_y = 100;
// 	map_size = 12;
// 	tile_size = TILE_SIZE * MINIMAP_SCALE;
// 	border_size = map_size * tile_size;
// 	border_x = player_screen_x - border_size / 2;
// 	border_y = player_screen_y - border_size / 2;
// 	clear_layer(data->map_layer, WIN_HEIGHT * WIN_WIDTH);
// 	clear_layer(data->ray_layer, WIN_HEIGHT * WIN_WIDTH);
// 	mlx_put_rectangle_to_layer(data->map_layer, border_x, border_y, border_size,
// 		convert_to_hex(data->mapdata->c_rgb));
// 	draw_line(data->map_layer, border_x, border_y, border_x + border_size,
// 		border_y, 0xFFFFFF);
// 	// Bottom line
// 	draw_line(data->map_layer, border_x, border_y + border_size, border_x
// 		+ border_size, border_y + border_size, 0xFFFFFF);
// 	// Left line
// 	draw_line(data->map_layer, border_x, border_y, border_x, border_y
// 		+ border_size, 0xFFFFFF);
// 	// Right line
// 	draw_line(data->map_layer, border_x + border_size, border_y, border_x
// 		+ border_size, border_y + border_size, 0xFFFFFF);
// 	// Calculate bounds for visible map section
// 	start_x = (int)data->player->x_pos - map_size / 2;
// 	start_y = (int)data->player->y_pos - map_size / 2;
// 	end_x = start_x + map_size;
// 	end_y = start_y + map_size;
// 	// Clamp bounds to map edges
// 	start_x = fmax(0, start_x);
// 	start_y = fmax(0, start_y);
// 	end_x = fmin(end_x, data->mapdata->width);
// 	end_y = fmin(end_y, data->mapdata->height);
// 	player_screen_pos_x = player_screen_x + tile_size / 2;
// 	player_screen_pos_y = player_screen_y + tile_size / 2;
// 	// Update animation frame globally
// 	if (frame_count++ >= 10) // Same speed as animate_sprites
// 	{
// 		frame = (frame + 1) % 5; // 5 frames like animate_sprites
// 		frame_count = 0;
// 	}
// 	// Draw visible map tiles
// 	for (y = start_y; y < end_y; y++)
// 	{
// 		for (x = start_x; x < end_x; x++)
// 		{
// 			if (x < 0 || y < 0 || x >= data->mapdata->width
// 				|| y >= data->mapdata->height)
// 				continue ;
// 			// Calculate tile positions relative to player
// 			pos_x = player_screen_pos_x + ((x - data->player->x_pos)
// 					* tile_size);
// 			pos_y = player_screen_pos_y + ((y - data->player->y_pos)
// 					* tile_size);
// 			if (pos_x - tile_size / 2 < border_x || pos_x + tile_size
// 				/ 2 > border_x + border_size || pos_y - tile_size / 2 < border_y
// 				|| pos_y + tile_size / 2 > border_y + border_size)
// 				continue ;
// 			// Draw tiles centered on their positions
// 			if (data->mapdata->map[y][x] == '1')
// 			{
// 				mlx_put_rectangle_to_layer(data->map_layer, pos_x - tile_size
// 					/ 2, pos_y - tile_size / 2, tile_size,
// 					convert_to_hex(data->mapdata->f_rgb));
// 			}
// 			else if (data->mapdata->map[y][x] == 'D')
// 			{
// 				// Draw door using lines based on orientation
// 				if (data->mapdata->door_states[y][x] == OPENING
// 					|| data->mapdata->door_states[y][x] == CLOSING)
// 				{
// 					slide_offset = data->mapdata->door_timers[y][x];
// 					if (data->mapdata->door_states[y][x] == CLOSING)
// 						slide_offset = 1.0 - slide_offset;
// 					// Check door orientation by looking at adjacent walls
// 					is_vertical = (x > 0 && data->mapdata->map[y][x - 1] == '1')
// 						|| (x < data->mapdata->width - 1
// 							&& data->mapdata->map[y][x + 1] == '1');
// 					if (is_vertical)
// 					{
// 						// Vertical door (East-West walls)
// 						draw_line(data->map_layer, pos_x - tile_size / 2
// 							+ (slide_offset * tile_size), pos_y - tile_size / 2,
// 							pos_x - tile_size / 2 + (slide_offset * tile_size),
// 							pos_y + tile_size / 2, 0xAAAAAA);
// 					}
// 					else
// 					{
// 						// Horizontal door (North-South walls)
// 						draw_line(data->map_layer, pos_x - tile_size / 2, pos_y
// 							- tile_size / 2 + (slide_offset * tile_size), pos_x
// 							+ tile_size / 2, pos_y - tile_size / 2
// 							+ (slide_offset * tile_size), 0xAAAAAA);
// 					}
// 				}
// 				else if (data->mapdata->door_states[y][x] == CLOSED)
// 				{
// 					// Same orientation check for closed doors
// 					is_vertical = (x > 0 && data->mapdata->map[y][x - 1] == '1')
// 						|| (x < data->mapdata->width - 1
// 							&& data->mapdata->map[y][x + 1] == '1');
// 					if (!is_vertical)
// 					{
// 						draw_line(data->map_layer, pos_x - tile_size / 2, pos_y
// 							- tile_size / 2, pos_x - tile_size / 2, pos_y
// 							+ tile_size / 2, 0xAAAAAA);
// 					}
// 					else
// 					{
// 						draw_line(data->map_layer, pos_x - tile_size / 2, pos_y
// 							- tile_size / 2, pos_x + tile_size / 2, pos_y
// 							- tile_size / 2, 0xAAAAAA);
// 					}
// 				}
// 			}
// 			else if (data->mapdata->map[y][x] == 'C')
// 			{
// 				current_sprite = data->text_sprite_buffer[frame];
// 				if (current_sprite && current_sprite->img)
// 				{
// 					// Calculate sprite dimensions
// 					int sprite_size = tile_size / 2;
// 						// Make sprite smaller than tile
// 					for (int texY = 0; texY < SPRITE_SIZE; texY++)
// 					{
// 						for (int texX = 0; texX < SPRITE_SIZE; texX++)
// 						{
// 							// Get pixel from sprite texture
// 							sprite_pixel = current_sprite->addr + (texY
// 									* current_sprite->line_length + texX
// 									* (current_sprite->bits_per_pixel / 8));
// 							// Calculate position on minimap
// 							draw_x = pos_x - sprite_size / 2 + (texX
// 									* sprite_size / SPRITE_SIZE);
// 							draw_y = pos_y - sprite_size / 2 + (texY
// 									* sprite_size / SPRITE_SIZE);
// 							// Draw pixel if not transparent
// 							color = *(unsigned int *)sprite_pixel;
// 							if (color != 0xFF000000)
// 							{
// 								put_pixel_to_layer(data->map_layer, draw_x,
// 									draw_y, color);
// 							}
// 						}
// 					}
// 				}
// 				else
// 				{
// 					// Fallback rectangle if sprite isn't loaded
// 					mlx_put_rectangle_to_layer(data->map_layer, pos_x
// 						- tile_size / 4, pos_y - tile_size / 4, tile_size / 2,
// 						0xFFFF00);
// 				}
// 			}
// 		}
// 	}
// 	// Draw rays with same scaling as tiles
// 	double ray_start_x, ray_start_y, ray_end_x, ray_end_y;
// 	for (int i = 0; i < NUM_RAYS; i++)
// 	{
// 		ray_start_x = player_screen_x + 1;
// 		ray_start_y = player_screen_y;
// 		ray_end_x = player_screen_x + (data->rays[i].wall_hit_x * tile_size);
// 		ray_end_y = player_screen_y + (data->rays[i].wall_hit_y * tile_size);
// 		draw_line(data->ray_layer, (int)ray_start_x, (int)ray_start_y,
// 			(int)ray_end_x, (int)ray_end_y, 0xFFFF01);
// 	}
// 	// Draw player
// 	mlx_put_rectangle_to_layer(data->ray_layer, player_screen_x - (PLAYER_SIZE
// 			* MINIMAP_SCALE) / 2, player_screen_y - (PLAYER_SIZE
// 			* MINIMAP_SCALE) / 2, PLAYER_SIZE * MINIMAP_SCALE, 0xFF0000);
// }
