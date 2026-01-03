/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:37:32 by edelplan          #+#    #+#             */
/*   Updated: 2024/10/07 15:17:19 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)

{
	char	*dest;
	int		len;

	if (!s1 || !s2 || (!s1 && !s2))
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = (char *)ft_calloc(len, sizeof(char));
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1, ft_strlen(s1));
	ft_strlcat(dest, s2, len);
	return (dest);
}

/*static	int	ft_total_len(char const	*s1, char const	*s2)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (s1[i])
	{
		total = total + ft_strlen(s1[i]);
		i++;
	}
	total = total * ft_strlen(s2) + 1;
	return (total);
}*/
