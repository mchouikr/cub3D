/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:08:04 by edelplan          #+#    #+#             */
/*   Updated: 2024/06/06 16:43:18 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int nb, int base)
{
	char	*str;
	int		len;
	long	n;

	n = nb;
	len = ft_int_len_base(n, base);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (nb == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	len = len - 1;
	while (n > 0)
	{
		str[len] = "0123456789abcdef"[n % base];
		n = n / base;
		len--;
	}
	return (str);
}
/*
#include <stdio.h>
int	main()
{
	//printf("%s", ft_itoa_rad(156, 16));
	ft_putstr_fd(ft_itoa_rad(123456789, 16), 1);

}*/
//Count the number of int
//Return a string by printing each nb in reverse from the len.
// -n to reverse negative number and just add - in first position of string.
