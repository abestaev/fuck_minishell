/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbrs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:05:20 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/06/09 10:36:39 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int fd, int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (ft_putstr(fd, "-2147483648"));
	if (n < 0)
	{
		i += ft_putchar(fd, '-');
		n *= -1;
	}
	if (n > 9)
	{
		i += ft_putnbr(fd, n / 10);
		i += ft_putnbr(fd, n % 10);
	}
	else
		i += ft_putchar(fd, n + 48);
	return (i);
}

int	ft_unsigned_putnbr(int fd, unsigned int n)
{
	int	i;

	i = 0;
	if (n > 9)
	{
		i += ft_putnbr(fd, n / 10);
		i += ft_putnbr(fd, n % 10);
	}
	else
		i += ft_putchar(fd, n + 48);
	return (i);
}

int	ft_puthexa(int fd, unsigned long n, char c)
{
	int		i;
	char	*hex;
	char	*hexa;

	i = 0;
	hex = "0123456789abcdef";
	hexa = "0123456789ABCDEF";
	if (n < 16 && c == 'x')
		i += ft_putchar(fd, hex[n]);
	else if (n < 16 && c == 'X')
		i += ft_putchar(fd, hexa[n]);
	else if (n >= 16)
	{
		i += ft_puthexa(fd, n / 16, c);
		i += ft_puthexa(fd, n % 16, c);
	}
	return (i);
}

int	ft_putptr(int fd, unsigned long n)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		i += ft_putstr(fd, "(nil)");
		return (i);
	}
	else
	{
		i += ft_putstr(fd, "0x");
		i += ft_puthexa(fd, n, 'x');
	}
	return (i);
}
