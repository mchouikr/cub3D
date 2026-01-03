/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:08:04 by edelplan          #+#    #+#             */
/*   Updated: 2024/05/28 15:27:25 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(long int nb)
{
	int	count;

	count = 0;
	if (nb < 0)
	{
		count++;
		nb = -nb;
	}
	if (nb == 0)
		count++;
	while (nb != 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int nb)
{
	char	*str;
	int		len;
	long	n;

	n = nb;
	len = int_len(n);
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
		str[len] = ((n % 10) + '0');
		n = n / 10;
		len--;
	}
	return (str);
}

//Count the number of int
//Return a string by printing each nb in reverse from the len.
// -n to reverse negative number and just add - in first position of string.
