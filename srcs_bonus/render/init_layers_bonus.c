/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_layers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:13:30 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/17 22:13:57 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	init_layers(t_data *data)
{
	define_width_and_height(data);
	data->map_layer = malloc(sizeof(t_img));
	if (data->map_layer == NULL)
		return (FAILURE);
	data->player_layer = malloc(sizeof(t_img));
	if (data->player_layer == NULL)
		return (FAILURE);
	data->ray_layer = malloc(sizeof(t_img));
	if (data->ray_layer == NULL)
		return (FAILURE);
	data->wall_layer = malloc(sizeof(t_img));
	if (data->wall_layer == NULL)
		return (FAILURE);
	data->global_layer = malloc(sizeof(t_img));
	if (data->global_layer == NULL)
		return (FAILURE);
	data->sprite_layer = malloc(sizeof(t_img));
	if (data->sprite_layer == NULL)
		return (FAILURE);
	init_layers_buffer(data);
	return (SUCCESS);
}
