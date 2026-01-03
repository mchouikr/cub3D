/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:03:22 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 00:07:06 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	draw_sprite_stripes(t_data *data, t_sprite_calc *sp)
{
	int	stripe;

	stripe = sp->draw_start_x - 1;
	while (++stripe < sp->draw_end_x)
	{
		if (sp->transform_y > 0 && stripe >= 0 && stripe < WIN_WIDTH
			&& sp->transform_y < data->sprite->zbuffer[stripe])
		{
			sp->tex_x = calculate_tex_x(sp, stripe);
			draw_sprite_line(data, sp, stripe);
		}
	}
	update_frame_counter(data);
}

static void	calculate_sprite_bounds(t_sprite_calc *sp)
{
	sp->draw_start_y = -sp->height / 2 + WIN_HEIGHT / 2;
	if (sp->draw_start_y < 0)
		sp->draw_start_y = 0;
	sp->draw_end_y = sp->height / 2 + WIN_HEIGHT / 2;
	if (sp->draw_end_y >= WIN_HEIGHT)
		sp->draw_end_y = WIN_HEIGHT - 1;
	sp->draw_start_x = -sp->width / 2 + sp->screen_x;
	if (sp->draw_start_x < 0)
		sp->draw_start_x = 0;
	sp->draw_end_x = sp->width / 2 + sp->screen_x;
	if (sp->draw_end_x >= WIN_WIDTH)
		sp->draw_end_x = WIN_WIDTH - 1;
}

static void	calculate_sprite_dims(t_data *data, t_sprite_calc *calc)
{
	calc->inv_det = 1.0 / (data->camera->plane_x * data->camera->dir_y
			- data->camera->dir_x * data->camera->plane_y);
	calc->transform_x = calc->inv_det * (data->camera->dir_y * calc->sprite_x
			- data->camera->dir_x * calc->sprite_y);
	calc->transform_y = calc->inv_det * (-data->camera->plane_y * calc->sprite_x
			+ data->camera->plane_x * calc->sprite_y);
	calc->screen_x = (int)((WIN_WIDTH / 2) * (1 + calc->transform_x
				/ calc->transform_y));
	calc->height = abs((int)(WIN_HEIGHT / calc->transform_y / 3));
	calc->width = calc->height;
	calc->current_sprite = data->text_sprite_buffer[data->sprite->frame];
	calculate_sprite_bounds(calc);
}

void	draw_sprites(t_data *data)
{
	t_sprite_calc	calc;
	int				i;
	int				sprite_pos;

	update_sprite_positions(data);
	if (!data || !data->sprite || !data->mapdata)
		return ;
	sort_sprites(data);
	i = 0;
	while (i < data->sprite->num_sprites)
	{
		sprite_pos = data->sprite->order[i];
		calc.sprite_x = (sprite_pos % data->mapdata->width + 0.5)
			- data->player->x_pos;
		calc.sprite_y = (sprite_pos / data->mapdata->width + 0.5)
			- data->player->y_pos;
		calculate_sprite_dims(data, &calc);
		draw_sprite_stripes(data, &calc);
		i++;
	}
}
