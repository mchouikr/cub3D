/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:51:18 by mchouikr          #+#    #+#             */
/*   Updated: 2024/10/15 12:28:38 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ptr_len(uintptr_t num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	ft_put_ptr_fd(int fd, uintptr_t ptr)
{
	if (ptr >= 16)
	{
		ft_put_ptr_fd(fd, ptr / 16);
		ft_put_ptr_fd(fd, ptr % 16);
	}
	else
	{
		if (ptr <= 9)
			ft_print_char_fd(fd, ptr + '0');
		else
			ft_print_char_fd(fd, ptr - 10 + 'a');
	}
}

int	ft_print_addr_fd(int fd, unsigned long long ptr)
{
	int	count;

	count = 0;
	if (ptr == 0)
	{
		ft_print_str_fd(fd, "(nil)");
		return (5);
	}
	count += write(1, "0x", 2);
	ft_put_ptr_fd(fd, ptr);
	count += ft_ptr_len(ptr);
	return (count);
}

int	ft_print_digit_fd(int fd, long n, int base)
{
	int		count;
	char	*symbols;

	symbols = "0123456789abcdef";
	if (n < 0)
	{
		write(1, "-", 1);
		return (ft_print_digit_fd(fd, -n, base) + 1);
	}
	else if (n < base)
		return (ft_print_char_fd(fd, symbols[n]));
	else
	{
		count = ft_print_digit_fd(fd, n / base, base);
		return (count + ft_print_digit_fd(fd, n % base, base));
	}
}

int	ft_print_maj_digit_fd(int fd, long n, int base)
{
	int		count;
	char	*symbols;

	symbols = "0123456789ABCDEF";
	if (n < 0)
	{
		write(1, "-", 1);
		return (ft_print_maj_digit_fd(fd, -n, base) + 1);
	}
	else if (n < base)
		return (ft_print_char_fd(fd, symbols[n]));
	else
	{
		count = ft_print_maj_digit_fd(fd, n / base, base);
		return (count + ft_print_maj_digit_fd(fd, n % base, base));
	}
}
