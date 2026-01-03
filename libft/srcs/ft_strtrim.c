/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:59:25 by edelplan          #+#    #+#             */
/*   Updated: 2024/05/30 15:41:03 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	len;
	size_t	start;
	size_t	end;

	len = 0;
	end = ft_strlen(s1);
	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	len = end - start + 1;
	trim = (char *)ft_calloc(len, sizeof(char));
	if (!trim)
		return (NULL);
	ft_strlcpy(trim, s1 + start, len);
	return (trim);
}

//Trim all the found character at beginning and end of string
// Using strchr to find the *set in s1 and calculate len from here
//Using len and calloc to allocate and strlcpy to return the trimmed string.
