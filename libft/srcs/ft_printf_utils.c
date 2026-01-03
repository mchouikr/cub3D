/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:25:00 by edelplan          #+#    #+#             */
/*   Updated: 2024/08/30 18:10:50 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd_c(const char *s, int fd, int *count)
{
	if (fd < 0)
		return (0);
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (*count = 6);
	}
	while (*s)
	{
		ft_putchar_fd_c(*s, 1, count);
		s++;
	}
	return (*count);
}

int	ft_putchar_fd_c(char c, int fd, int *count)
{
	write(fd, &c, sizeof(c));
	(*count)++;
	return (*count);
}

int	ft_putnbr_printf(long nb, int uppercase, int base, int *count)
{
	const char	*base_lower;
	const char	*base_upper;
	const char	*digits;

	base_lower = "0123456789abcdef";
	base_upper = "0123456789ABCDEF";
	digits = base_lower;
	if (uppercase == 1)
		digits = base_upper;
	if (nb < 0 && base == 10)
	{
		ft_putchar_fd_c('-', 1, count);
		nb = -nb;
	}
	if (nb >= base)
		ft_putnbr_printf(nb / base, uppercase, base, count);
	ft_putchar_fd_c(digits[nb % base], 1, count);
	return (*count);
}

int	ft_putnbr_printf_u(unsigned long nb, int base, int *count)
{
	if (nb >= (unsigned)base)
		ft_putnbr_printf_u((nb / base), base, count);
	ft_putchar_fd_c("0123456789abcdef"[nb % base], 1, count);
	return (*count);
}

// Couldnt figure out a way of returning
// an unsigned only in certain cases, so two functions for that.
// unsigned long for handlin %p and %u
