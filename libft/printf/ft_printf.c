/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:34:48 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/06/09 10:54:31 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_param(va_list args, char c, int i, int fd)
{
	if (c == 's')
		i += ft_putstr(fd, va_arg(args, char *));
	else if (c == 'c')
		i += ft_putchar(fd, va_arg(args, int));
	else if (c == 'p')
		i += ft_putptr(fd, va_arg(args, size_t));
	else if (c == 'd' || c == 'i')
		i += ft_putnbr(fd, va_arg(args, int));
	else if (c == 'u')
		i += ft_unsigned_putnbr(fd, va_arg(args, unsigned int));
	else if (c == 'x')
		i += ft_puthexa(fd, va_arg(args, unsigned int), 'x');
	else if (c == 'X')
		i += ft_puthexa(fd, va_arg(args, unsigned int), 'X');
	else if (c == '%')
		i += ft_putchar(fd, c);
	return (i);
}

__attribute__((destructor)) void ft_flush(void)
{
	ft_putchar(-42, 0);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	va_start(args, s);
	if (!s)
		return (-1);
	while (s[j])
	{
		if (s[j] == '%')
		{
			j++;
			i = ft_param(args, s[j], i, 1);
		}
		else
			i += ft_putchar(1, s[j]);
		j++;
	}
	va_end(args);
	return (i);
}

int	ft_dprintf(int fd, const char *s, ...)
{
	va_list	args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	va_start(args, s);
	if (!s)
		return (-1);
	while (s[j])
	{
		if (s[j] == '%')
		{
			j++;
			i = ft_param(args, s[j], i, fd);
		}
		else
			i += ft_putchar(fd, s[j]);
		j++;
	}
	va_end(args);
	return (i);
}
