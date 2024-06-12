/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:10:51 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/06/09 10:36:05 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1024

int	ft_printf(const char *s, ...);
int	ft_dprintf(int fd, const char *s, ...);
int	ft_putchar(int fd, char c);
int	ft_putstr(int fd, const char *str);
int	ft_putnbr(int fd, int n);
int	ft_unsigned_putnbr(int fd, unsigned int n);
int	ft_puthexa(int fd, unsigned long n, char c);
int	ft_putptr(int fd, unsigned long n);

#endif