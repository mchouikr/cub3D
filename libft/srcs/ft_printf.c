/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:31:11 by edelplan          #+#    #+#             */
/*   Updated: 2024/09/30 18:10:14 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_handle_string(char *str, int fd, int *count)
{
	if (str == NULL)
		ft_putstr_fd_c("(null)", fd, count);
	else
		ft_putstr_fd_c(str, fd, count);
	return (*count);
}

static int	ft_handle_ptr(uintptr_t ptr, int *count)
{
	if (ptr == 0)
		ft_putstr_fd_c("(nil)", 1, count);
	else
	{
		ft_putstr_fd_c("0x", 1, count);
		ft_putnbr_printf_u(ptr, 16, count);
	}
	return (*count);
}

static int	ft_handle_spec(const char *format, va_list args, int *count)
{
	if (*(format) == 'x')
		ft_putnbr_printf(va_arg(args, unsigned int), 0, 16, count);
	else if (*format == 'X')
		ft_putnbr_printf(va_arg(args, unsigned int), 1, 16, count);
	else if (*(format) == 'd' || *(format) == 'i')
		ft_putnbr_printf((int)va_arg(args, int), 0, 10, count);
	else if (*(format) == 'u')
		ft_putnbr_printf_u(va_arg(args, unsigned int), 10, count);
	else if (*(format) == 'c')
		ft_putchar_fd_c((char)va_arg(args, int), 1, count);
	else if (*(format) == '%')
		ft_putchar_fd_c('%', 1, count);
	else if (*(format) == 's')
		ft_handle_string(va_arg(args, char *), 1, count);
	else if (*(format) == 'p')
		ft_handle_ptr(va_arg(args, uintptr_t), count);
	return (*count);
}

int	ft_print_args(const char *format, va_list args, int *count)
{
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ft_handle_spec(format, args, count);
			format++;
		}
		else
			ft_putchar_fd_c(*format++, 1, count);
	}
	return (*count);
}

int	ft_printf(const char *format, ...)
{
	int		countf;
	va_list	args;

	countf = 0;
	va_start(args, format);
	if (!format)
		return (-1);
	countf = ft_print_args(format, args, &countf);
	va_end(args);
	return (countf);
}

/*
int	main(void)
{
	int	ret;
	int	re2;

	re2 = ft_printf(0);
	ret = ft_printf(NULL);
	ft_printf("%d\n", ret);
	ft_printf("%d", re2);
	return (0);
}*/

// Handle string for %s exceptions
// Handle ptr to append 0x to the address / memory location
// Handle spec manage each case
// Print arg handle skipping % and specifier if encountered
// Call handle_spec for the actual printing.
// Print the string if % is not encountered.
// Correctly handling the return value of -1 if print if there is any
//Issue with the input string.
