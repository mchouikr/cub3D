/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:58:36 by edelplan          #+#    #+#             */
/*   Updated: 2024/05/25 12:17:16 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*last;

	last = str;
	while (*last)
		last++;
	while (last >= str)
	{
		if (*last == (char)c)
			return ((char *)last);
		last--;
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}
//	if (str == NULL)
//		return (NULL);
