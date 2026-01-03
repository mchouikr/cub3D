/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_presence_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:44:03 by mchouikr          #+#    #+#             */
/*   Updated: 2025/02/12 11:49:07 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	skip_spaces(t_parse *parse)
{
	while (ft_isspace(*parse->tmp))
		parse->tmp++;
}

int	check_empty_line(t_parse *parse, int *i)
{
	if (*parse->tmp == '\0')
	{
		(*i)++;
		parse->count++;
		return (1);
	}
	return (0);
}

int	handle_prefixes_part1(t_parse *parse, char *line)
{
	if (!ft_strncmp(parse->tmp, NO, 3))
	{
		parse->count += ft_strlen(line);
		parse->data_counter++;
		if (parse->textures_found[0] == false)
			parse->textures_found[0] = true;
		else
			return (ft_fprintf(2, TEXTURES_ERROR), FAILURE);
		return (SUCCESS);
	}
	else if (!ft_strncmp(parse->tmp, SO, 3))
	{
		parse->count += ft_strlen(line);
		parse->data_counter++;
		if (parse->textures_found[1] == false)
			parse->textures_found[1] = true;
		else
			return (ft_fprintf(2, TEXTURES_ERROR), FAILURE);
		return (SUCCESS);
	}
	return (2);
}

int	handle_prefixes_part2(t_parse *parse, char *line)
{
	if (!ft_strncmp(parse->tmp, WE, 3))
	{
		parse->count += ft_strlen(line);
		parse->data_counter++;
		if (parse->textures_found[2] == false)
			parse->textures_found[2] = true;
		else
			return (ft_fprintf(2, TEXTURES_ERROR), FAILURE);
		return (SUCCESS);
	}
	else if (!ft_strncmp(parse->tmp, EA, 3))
	{
		parse->count += ft_strlen(line);
		parse->data_counter++;
		if (parse->textures_found[3] == false)
			parse->textures_found[3] = true;
		else
			return (ft_fprintf(2, TEXTURES_ERROR), FAILURE);
		return (SUCCESS);
	}
	return (2);
}

int	handle_prefixes_part3(t_parse *parse, char *line)
{
	if (!ft_strncmp(parse->tmp, F, 2))
	{
		parse->count += ft_strlen(line);
		parse->data_counter++;
		if (parse->textures_found[4] == false)
			parse->textures_found[4] = true;
		else
			return (ft_fprintf(2, TEXTURES_ERROR), FAILURE);
		return (SUCCESS);
	}
	else if (!ft_strncmp(parse->tmp, C, 2))
	{
		parse->count += ft_strlen(line);
		parse->data_counter++;
		if (parse->textures_found[5] == false)
			parse->textures_found[5] = true;
		else
			return (ft_fprintf(2, TEXTURES_ERROR), FAILURE);
		return (SUCCESS);
	}
	return (2);
}
