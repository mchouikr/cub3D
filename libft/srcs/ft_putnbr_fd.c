/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:29:51 by edelplan          #+#    #+#             */
/*   Updated: 2024/05/28 15:34:03 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = nb * -1;
	}
	if (nb > 9)
		ft_putnbr_fd((nb / 10), fd);
	ft_putchar_fd(nb % 10 + '0', fd);
}

/*
This is just a less glorified iota that return nothing and just write.
Doesn't allocate shit either.

void	ft_putnbr_fd(int n, int fd)
{
	ft_putstr_fd(ft_itoa(n),fd);
}}*/
