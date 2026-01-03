/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:03:35 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/12 14:48:18 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	update_movement(t_data *data, int ud_direction, int lr_direction)
{
	double	next_x;
	double	next_y;

	next_x = data->player->x_pos;
	next_y = data->player->y_pos;
	next_x = data->player->x_pos + cos(data->player->rot_angle) * ud_direction
		* PLAYER_SPEED;
	next_y = data->player->y_pos + sin(data->player->rot_angle) * ud_direction
		* PLAYER_SPEED;
	next_x = next_x + (cos(data->player->rot_angle + M_PI / 2) * lr_direction
			* PLAYER_SPEED);
	next_y = next_y + (sin(data->player->rot_angle + M_PI / 2) * lr_direction
			* PLAYER_SPEED);
	if (!check_collision(data, next_x, next_y))
	{
		data->player->x_pos = next_x;
		data->player->y_pos = next_y;
	}
}

static void	define_directions(t_data *data, double *ud_direction,
		double *lr_direction)
{
	if (data->input->w_pressed)
		*ud_direction = 1;
	if (data->input->a_pressed)
		*lr_direction = -1;
	if (data->input->s_pressed)
		*ud_direction = -1;
	if (data->input->d_pressed)
		*lr_direction = 1;
}

void	movement_handler(t_data *data)
{
	double	turn_direction;
	double	ud_direction;
	double	lr_direction;
	float	mouse_center;

	mouse_center = WIN_WIDTH / 2;
	turn_direction = 0;
	ud_direction = 0;
	lr_direction = 0;
	define_directions(data, &ud_direction, &lr_direction);
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &data->input->mouse_x,
		&data->input->mouse_y);
	if (data->input->left_pressed || data->input->mouse_x - mouse_center < 0)
	{
		turn_direction = -1;
		update_camera_plane(data, turn_direction);
	}
	if (data->input->right_pressed || data->input->mouse_x - mouse_center > 0)
	{
		turn_direction = 1;
		update_camera_plane(data, turn_direction);
	}
	update_rotation(data, turn_direction);
	update_movement(data, ud_direction, lr_direction);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		on_destroy(data);
		exit(0);
	}
	if (keysym == XK_w)
		data->input->w_pressed = 1;
	if (keysym == XK_a)
		data->input->a_pressed = 1;
	if (keysym == XK_s)
		data->input->s_pressed = 1;
	if (keysym == XK_d)
		data->input->d_pressed = 1;
	if (keysym == XK_Left)
		data->input->left_pressed = 1;
	if (keysym == XK_Right)
		data->input->right_pressed = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == XK_w)
		data->input->w_pressed = 0;
	if (keysym == XK_a)
		data->input->a_pressed = 0;
	if (keysym == XK_s)
		data->input->s_pressed = 0;
	if (keysym == XK_d)
		data->input->d_pressed = 0;
	if (keysym == XK_Left)
		data->input->left_pressed = 0;
	if (keysym == XK_Right)
		data->input->right_pressed = 0;
	return (0);
}
