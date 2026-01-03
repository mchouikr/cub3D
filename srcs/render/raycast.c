/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:45:31 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/05 01:20:11 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_and_check_ray(t_data *data, t_ray *ray, int ray_id, t_dda *dda)
{
	double	fov_rad;
	double	half_fov;
	double	camera_x;

	fov_rad = (FOV * M_PI / 180.0);
	half_fov = fov_rad / 2.0;
	camera_x = 2 * ray_id / (double)NUM_RAYS - 1;
	ray->wall_dir = (t_wall_dir){false, false, false, false};
	data->camera->dir_x = cos(data->player->rot_angle);
	data->camera->dir_y = sin(data->player->rot_angle);
	data->camera->plane_x = -data->camera->dir_y * tan(half_fov);
	data->camera->plane_y = data->camera->dir_x * tan(half_fov);
	ray->ray_dir_x = data->camera->dir_x + data->camera->plane_x * camera_x;
	ray->ray_dir_y = data->camera->dir_y + data->camera->plane_y * camera_x;
	if (ray->ray_dir_x == 0.0f)
		ray->ray_dir_x = 1e-6;
	if (ray->ray_dir_y == 0.0f)
		ray->ray_dir_y = 1e-6;
	dda->map_x = (int)data->player->x_pos;
	dda->map_y = (int)data->player->y_pos;
	dda->delta_dist_x = fabs(1 / ray->ray_dir_x);
	dda->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	init_ray_steps(t_data *data, t_ray *ray, t_dda *dda)
{
	if (ray->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (data->player->x_pos - dda->map_x)
			* dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - data->player->x_pos)
			* dda->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (data->player->y_pos - dda->map_y)
			* dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - data->player->y_pos)
			* dda->delta_dist_y;
	}
}

static void	perform_dda(t_data *data, t_dda *dda)
{
	int	hit;

	hit = 0;
	while (!hit && wall_hit(data, dda->map_x, dda->map_y) == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
	}
}

static void	handle_wall_hit(t_ray *ray, t_dda *dda)
{
	if (dda->side == 0)
	{
		ray->distance = dda->side_dist_x - dda->delta_dist_x;
		ray->wall_hit_x = ray->ray_dir_x * ray->distance;
		ray->wall_hit_y = ray->ray_dir_y * ray->distance;
		ray->wall_dir.east = (ray->ray_dir_x < 0);
		ray->wall_dir.west = !ray->wall_dir.east;
		ray->hit_vertical = false;
	}
	else
	{
		ray->distance = dda->side_dist_y - dda->delta_dist_y;
		ray->wall_hit_x = ray->ray_dir_x * ray->distance;
		ray->wall_hit_y = ray->ray_dir_y * ray->distance;
		ray->wall_dir.south = (ray->ray_dir_y < 0);
		ray->wall_dir.north = !ray->wall_dir.south;
		ray->hit_vertical = true;
	}
}

void	cast_single_ray(t_data *data, t_ray *ray, int ray_id)
{
	t_dda	dda;

	init_and_check_ray(data, ray, ray_id, &dda);
	init_ray_steps(data, ray, &dda);
	perform_dda(data, &dda);
	handle_wall_hit(ray, &dda);
}

// RAYCASTING v0.00001 ANGLE_STEP CALCULATION NOT WORKING

// double	get_horz_inter(t_data *data, t_ray *ray, double *hit_x,
		//double *hit_y)
// {
// 	double x_intercept;
// 	double y_intercept;
// 	double rayAngle = normalize_angle(ray->angle);
// 	double x_step = 0;
// 	double y_step =0;
// 	double player_x = data->player->x_pos;
// 	double player_y = data->player->y_pos;

// 	//CES VALEURS SONT BONNES MAIS FONT PLANTER ENCORE PLUS
// 	// bool isRayFacingRight = rayAngle > 0 && rayAngle < M_PI;
// 	// bool isRayFacingDown = (rayAngle > M_PI / 2 && rayAngle < 3 * M_PI / 2);

// 	bool isRayFacingRight = cos(rayAngle) > 0;
// 	bool isRayFacingDown = sin(rayAngle) > 0;

// 	y_intercept = floor(player_y / TILE_SIZE) * TILE_SIZE;
// 	if (!isRayFacingDown)
// 		y_intercept += TILE_SIZE - 1;
// 	else
// 		y_intercept += TILE_SIZE + 1;
// 	x_intercept = player_x + (y_intercept - player_y) / tan(rayAngle);

// 	y_step = TILE_SIZE * sin(rayAngle);
// 	if (!isRayFacingDown)
// 		y_step *= -1;
// 	x_step = y_step / tan(rayAngle);
// 	if (!isRayFacingRight)
//         x_step *= -1;
// 	while(!wall_hit(data, x_intercept, y_intercept))
// 	{
// 		x_intercept += x_step;
// 		y_intercept += y_step;
// 	}
// 	*hit_x = x_intercept;
// 	*hit_y = y_intercept;
// 	return (hypot(x_intercept - player_x, y_intercept - player_y));
// 	//return (sqrt(pow(x_intercept - player_x, 2) + pow(y_intercept - player_y,
			//	2)));
// }

// double	get_vert_inter(t_data *data, t_ray *ray, double *hit_x,
		//double *hit_y)
// {
// 	double rayAngle = normalize_angle(ray->angle);
// 	double x_step = 0;
// 	double y_step =0;
// 	double player_x = data->player->x_pos;
// 	double player_y = data->player->y_pos;

// 	bool isRayFacingRight = cos(rayAngle) > 0;
// 	bool isRayFacingDown = sin(rayAngle) > 0;

// 	//CES VALEURS SONT BONNES MAIS FONT PLANTER ENCORE PLUS
// 	// bool isRayFacingRight = rayAngle > 0 && rayAngle < M_PI;
// 	// bool isRayFacingDown = (rayAngle > M_PI / 2 && rayAngle < 3 * M_PI / 2);

// 	double x_intercept;
// 	double y_intercept;

// 	x_intercept = floor(player_x / TILE_SIZE) * TILE_SIZE;
// 	if (isRayFacingRight)
// 		x_intercept += TILE_SIZE  - 1;
// 	else
// 		x_intercept += TILE_SIZE + 1;
// 	y_intercept = player_y + ((x_intercept - player_x) * tan(rayAngle));

// 	x_step = 1;
// 	if (!isRayFacingRight)
// 		x_step *= -1;
// 	y_step = x_step * tan(rayAngle);

//     if (!isRayFacingDown)
// 	{
//         y_step *= -1;
// 	}
// 	while(!wall_hit(data, x_intercept, y_intercept))
// 	{
// 		x_intercept += x_step;
// 		y_intercept += y_step;

// 	}
// 	*hit_x = x_intercept;
// 	*hit_y = y_intercept;
// 	return (hypot(x_intercept - player_x, y_intercept - player_y));
// }

// void cast_single_ray(t_data *data, t_ray *ray)
// {
// 	double	h_distance;
// 	double	v_distance;
// 	double h_hit_x, h_hit_y;
//     double v_hit_x, v_hit_y;
// 	ray->angle = normalize_angle(ray->angle);
// 	h_distance = get_horz_inter(data, ray, &h_hit_x, &h_hit_y);
// 	v_distance = get_vert_inter(data, ray, &v_hit_x, &v_hit_y);

//  	if (v_distance < h_distance)
//     {
//         ray->distance = v_distance;
//         ray->wall_hit_x = v_hit_x;
//         ray->wall_hit_y = v_hit_y;
//     }
//     else
//     {
//         ray->distance = h_distance;
//         ray->wall_hit_x = h_hit_x;
//         ray->wall_hit_y = h_hit_y;
//     }
// 	printf("H hit: x=%f, y=%f\n", h_hit_x, h_hit_y);
//     printf("V hit: x=%f, y=%f\n", v_hit_x, v_hit_y);
// }
// draw_walls(data);

// Debug
// int center = NUM_RAYS / 2;
// if (data->rays[center].wall_hit_x != 0 &&
//     data->rays[center].wall_hit_y != 0)
// {
//     printf("Center ray: angle=%f, distance=%.2f\n",
//            data->rays[center].angle,
//            data->rays[center].distance * TILE_SIZE);
// }
