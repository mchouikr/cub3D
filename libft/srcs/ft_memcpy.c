/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:47:47 by edelplan          #+#    #+#             */
/*   Updated: 2024/10/07 13:07:15 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*t_src;
	char		*t_dest;

	i = 0;
	t_src = (char *) src;
	t_dest = (char *) dest;
	if (n == 0 || dest == src)
		return (dest);
	while (i < n)
	{
		t_dest[i] = t_src[i];
		i++;
	}
	return (dest);
}

// Copy the memory from src to dest at most size n
