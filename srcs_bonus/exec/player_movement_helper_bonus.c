/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 23:02:47 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/17 23:04:56 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	handle_keyboard_input(t_data *data, double *ud_dir, double *lr_dir)
{
	if (data->input->w_pressed)
		*ud_dir = 1;
	if (data->input->a_pressed)
		*lr_dir = -1;
	if (data->input->s_pressed)
		*ud_dir = -1;
	if (data->input->d_pressed)
		*lr_dir = 1;
}

static void	handle_rotation_input(t_data *data, double *turn_dir)
{
	float	mouse_center;

	mouse_center = WIN_WIDTH / 2;
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &data->input->mouse_x,
		&data->input->mouse_y);
	if (data->input->left_pressed || data->input->mouse_x - mouse_center < 0)
		*turn_dir = -1;
	if (data->input->right_pressed || data->input->mouse_x - mouse_center > 0)
		*turn_dir = 1;
}

void	movement_handler(t_data *data)
{
	double	turn_direction;
	double	ud_direction;
	double	lr_direction;

	turn_direction = 0;
	ud_direction = 0;
	lr_direction = 0;
	handle_keyboard_input(data, &ud_direction, &lr_direction);
	handle_rotation_input(data, &turn_direction);
	if (turn_direction != 0)
		update_camera_plane(data, turn_direction);
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
	if (keysym == XK_space)
		data->input->space_pressed = 1;
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
	if (keysym == XK_space)
		data->input->space_pressed = 0;
	return (0);
}
