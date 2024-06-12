/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 03:18:24 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/06/09 11:29:09 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int fd, char c)
{
	static char	buff[BUFFER_SIZE + 1] = {0};
	static int	index = 0;
	static int	s_fd = 1;

	if (fd == -42 || index == BUFFER_SIZE)
	{
		if (write(s_fd, buff, index) < index)
			return (-1);
		index = 0;
		if (fd == -42)
			return (0);
	}
	s_fd = fd;
	buff[index++] = c;
	if (c == '\n')
	{
		if (write(s_fd, buff, index) < index)
			return (-1);
		index = 0;
	}
	return (1);
}

int	ft_putstr(int fd, const char *str)
{
	int	i;

	if (!str)
		return (ft_putstr(fd, "(null)"));
	i = 0;
	while (str[i])
		ft_putchar(fd, str[i++]);
	return (i);
}
