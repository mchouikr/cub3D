/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:32:32 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/14 11:33:06 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_format_fd(int fd, char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_print_char_fd(fd, va_arg(ap, int));
	else if (specifier == 's')
		count += ft_print_str_fd(fd, va_arg(ap, char *));
	else if (specifier == 'd' || specifier == 'i')
		count += ft_print_digit_fd(fd, (long)(va_arg(ap, int)), 10);
	else if (specifier == 'x')
		count += ft_print_digit_fd(fd, (long)(va_arg(ap, unsigned int)), 16);
	else if (specifier == 'p')
		count += ft_print_addr_fd(fd, va_arg(ap, unsigned long long));
	else if (specifier == 'u')
		count += ft_print_un_digit_fd(fd, (unsigned long)(va_arg(ap, int)));
	else if (specifier == 'X')
		count += ft_print_maj_digit_fd(fd, (long)(va_arg(ap, unsigned int)),
				16);
	else if (specifier == '%')
		count += write(fd, &specifier, 1);
	return (count);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		count;

	if (!format)
		return (-1);
	va_start(ap, format);
	count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
			count += print_format_fd(fd, *(++format), ap);
		else
			count += write(fd, format, 1);
		++format;
	}
	va_end(ap);
	return (count);
}

// int	main(int ac, char **av)
// {
// 	int	fd;

// 	if (ac == 3)
// 	{
// 		fd = open(av[2], O_RDWR | O_TRUNC);
// 		ft_fprintf(fd, "%s\n", av[1]);
// 		close(fd);
// 	}
// 	return (0);
// }