/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:19:01 by mchouikr          #+#    #+#             */
/*   Updated: 2024/10/15 12:28:40 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_char_fd(int fd, int c)
{
	return (write(fd, &c, 1));
}

int	ft_print_str_fd(int fd, char *str)
{
	int	count;

	if (!str)
	{
		ft_print_str_fd(fd, "(null)");
		return (6);
	}
	count = 0;
	while (*str)
	{
		ft_print_char_fd(fd, (int)*str);
		count++;
		str++;
	}
	return (count);
}

int	ft_num_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	len = ft_num_len(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (NULL);
	num[len] = '\0';
	while (n != 0)
	{
		num[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (num);
}

int	ft_print_un_digit_fd(int fd, unsigned long n)
{
	int		count;
	char	*unum;

	count = 0;
	if (n == 0)
		count += write(fd, "0", 1);
	else
	{
		unum = ft_uitoa(n);
		count += ft_print_str_fd(fd, unum);
		free(unum);
	}
	return (count);
}
