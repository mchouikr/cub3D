/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:26:18 by edelplan          #+#    #+#             */
/*   Updated: 2024/05/29 15:19:17 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *search, size_t len)
{
	size_t	i;

	i = 0;
	if (!ft_strlen(search))
		return ((char *) str);
	if (!*str)
		return (NULL);
	while (i < len)
	{
		if (ft_strncmp((char *)&str[i], search, ft_strlen(search)) == 0)
		{
			if (i + ft_strlen(search) > len)
				return (NULL);
			return ((char *) &str[i]);
		}
		i++;
	}
	return (NULL);
}

//Segfault in OG function when null is sent to STR or minus value to len
// Remove line 20 and the !*str part in line 23 to make it segfault.
//Line 20 using ft_strlen instead of !search or search[0] protect from
//some rare cases.
//Line 22 add ft_strlen(search) > len for protection against bad entry maybe.

//strncmp search and str at max len of search
// if i and search are superior to len then search is finished.
