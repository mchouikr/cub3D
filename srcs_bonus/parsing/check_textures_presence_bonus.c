/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_presence.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:32:59 by mchouikr          #+#    #+#             */
/*   Updated: 2025/02/17 10:50:37 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	check_lines(t_parse *parse, char **texture_data, int *i)
{
	int	ret;

	parse->tmp = texture_data[*i];
	skip_spaces(parse);
	if (check_empty_line(parse, i) == 1)
		return (CONTINUE);
	ret = handle_prefixes_part1(parse, texture_data[*i]);
	if (ret == FAILURE)
		return (FAILURE);
	if (ret != 2)
		return (SUCCESS);
	ret = handle_prefixes_part2(parse, texture_data[*i]);
	if (ret == FAILURE)
		return (FAILURE);
	if (ret != 2)
		return (SUCCESS);
	ret = handle_prefixes_part3(parse, texture_data[*i]);
	if (ret == FAILURE)
		return (FAILURE);
	if (ret != 2)
		return (SUCCESS);
	ft_fprintf(2, INVALID_DATA);
	return (FAILURE);
}

static int	check_textures_loop(t_parse *parse, char **texture_data)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (texture_data[i])
	{
		status = check_lines(parse, texture_data, &i);
		if (status == FAILURE)
			return (FAILURE);
		else if (status == CONTINUE)
			continue ;
		if (parse->data_counter > 6)
			return (ft_fprintf(2, TEXTURES_ERROR), FAILURE);
		else if (parse->data_counter == 6)
			break ;
		i++;
	}
	return (SUCCESS);
}

static int	all_textures_found(bool textures_found[])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (textures_found[i] == false)
		{
			ft_fprintf(2, TEXTURES_ERROR);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	check_textures_presence(char **texture_data, t_mapdata *mapdata)
{
	t_parse	*parse;

	parse = ft_calloc(1, sizeof(t_parse));
	if (!parse)
		return (ft_fprintf(2, DATA_INIT_FAIL), FAILURE);
	if (check_textures_loop(parse, texture_data) == FAILURE)
	{
		free(parse);
		return (FAILURE);
	}
	mapdata->start_map = parse->count + parse->data_counter;
	if (all_textures_found(parse->textures_found) == FAILURE)
	{
		free(parse);
		return (FAILURE);
	}
	free(parse);
	return (SUCCESS);
}

// int	check_lines(t_parse *parse, char **texture_data, int *i)
// {
// 	parse->tmp = texture_data[*i];
// 	skip_spaces(parse);
//     if (check_empty_line(parse, i) == 1)
// 		 return (CONTINUE);
// 	if (!ft_strncmp(parse->tmp, NO, 3))
// 	{
// 		parse->count += ft_strlen(texture_data[*i]);
// 		parse->data_counter++;
// 		if (parse->textures_found[0] == false)
// 			parse->textures_found[0] = true;
// 		else
// 			return (ft_fprintf(2, TEXTURES_ERROR), FAILURE);
// 	}
// 	else if (!ft_strncmp(parse->tmp, SO, 3))
// 	{
// 		parse->count += ft_strlen(texture_data[*i]);
// 		parse->data_counter++;
// 		if (parse->textures_found[1] == false)
// 			parse->textures_found[1] = true;
// 		else
// 			return (ft_fprintf(2, TEXTURES_ERROR), FAILURE);
// 	}
// 	else if (!ft_strncmp(parse->tmp, WE, 3))
// 	{
// 		parse->count += ft_strlen(texture_data[*i]);
// 		parse->data_counter++;
// 		if (parse->textures_found[2] == false)
// 			parse->textures_found[2] = true;
// 		else
// 			return (ft_fprintf(2, TEXTURES_ERROR), FAILURE);
// 	}
// 	else if (!ft_strncmp(parse->tmp, EA, 3))
// 	{
// 		parse->count += ft_strlen(texture_data[*i]);
// 		parse->data_counter++;
// 		if (parse->textures_found[3] == false)
// 			parse->textures_found[3] = true;
// 		else
// 			return (ft_fprintf(2, TEXTURES_ERROR), FAILURE);
// 	}
// 	else if (!ft_strncmp(parse->tmp, F, 2))
// 	{
// 		parse->count += ft_strlen(texture_data[*i]);
// 		parse->data_counter++;
// 		if (parse->textures_found[4] == false)
// 			parse->textures_found[4] = true;
// 		else
// 			return (ft_fprintf(2, TEXTURES_ERROR), FAILURE);
// 	}
// 	else if (!ft_strncmp(parse->tmp, C, 2))
// 	{
// 		parse->count += ft_strlen(texture_data[*i]);
// 		parse->data_counter++;
// 		if (parse->textures_found[5] == false)
// 			parse->textures_found[5] = true;
// 		else
// 			return (ft_fprintf(2, TEXTURES_ERROR), FAILURE);
// 	}
// 	else
// 		return (ft_fprintf(2, INVALID_DATA), FAILURE);
// 	return (SUCCESS);
// }