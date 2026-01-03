/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:37:06 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 00:07:06 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	update_dda_values(t_dda *dda)
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

static void	perform_dda(t_data *data, t_dda *dda, t_ray *ray)
{
	int		hit_type;
	double	t;

	hit_type = 0;
	while (hit_type == 0)
	{
		hit_type = wall_hit(data, dda->map_x, dda->map_y);
		if (hit_type == 2)
		{
			t = door_intersection(data, ray, dda);
			if (t > 0)
			{
				dda->door = 1;
				break ;
			}
			dda->door = 0;
			update_dda_values(dda);
			hit_type = 0;
		}
		else if (hit_type == 0)
			update_dda_values(dda);
	}
}

void	handle_door_hit(t_data *data, t_ray *ray, t_dda *dda)
{
	double	t;

	t = door_intersection(data, ray, dda);
	if (dda->door == 1 && t > 0)
	{
		ray->distance = t;
		ray->wall_hit_x = ray->ray_dir_x * ray->distance;
		ray->wall_hit_y = ray->ray_dir_y * ray->distance;
		ray->door_hit = 1;
		return ;
	}
	else
		ray->door_hit = 0;
}

static void	handle_wall_hit(t_data *data, t_ray *ray, t_dda *dda)
{
	(void)data;
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
	handle_door_hit(data, ray, dda);
}

void	cast_single_ray(t_data *data, t_ray *ray, int ray_id)
{
	t_dda	dda;

	init_and_check_ray(data, ray, ray_id, &dda);
	init_ray_steps(data, ray, &dda);
	perform_dda(data, &dda, ray);
	handle_wall_hit(data, ray, &dda);
	data->sprite->zbuffer[ray_id] = ray->distance;
}
