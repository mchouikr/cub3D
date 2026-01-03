/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:54:37 by edelplan          #+#    #+#             */
/*   Updated: 2024/05/28 15:38:57 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*t_src;
	char		*t_dest;

	i = 0;
	t_src = (char *) src;
	t_dest = (char *) dest;
	if (n == 0 || dest == src)
		return (dest);
	if (t_src > t_dest)
		ft_memcpy(t_dest, t_src, n);
	else
	{
		while (i != n)
		{
			t_dest[n - i - 1] = t_src[n - i - 1];
			i++;
		}
	}
	return (dest);
}

//Move memory at the beginning or at the end depending on the situation
//Therefore avoid overlap (n-- and i++ in
//the else will make the loop go backward but still
//return forward.)
