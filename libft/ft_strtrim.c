/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:28:53 by ssitchsa          #+#    #+#             */
/*   Updated: 2023/12/04 19:42:53 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	int		start;
	char	*trim;

	start = 0;
	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (s1[i] && is_char_set(set, s1[i]))
		i++;
	while (len > i && is_char_set(set, s1[len - 1]))
		len--;
	trim = malloc(sizeof(char) * (len - i + 1));
	if (!trim)
		return (NULL);
	while (i < len)
		trim[start++] = s1[i++];
	trim[start] = 0;
	return (trim);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char const	*s1;
// 	char const	*set;

// 	s1 = "  Neaue porro auisuiq  ";
// 	set = " ";
// 	printf("[%s]\n", ft_strtrim(s1, set));
// 	return (0);
// }
