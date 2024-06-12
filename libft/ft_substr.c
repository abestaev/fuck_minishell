/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:53:58 by ssitchsa          #+#    #+#             */
/*   Updated: 2023/12/05 16:12:35 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*empty(void)
{
	char	*err;

	err = malloc(1);
	if (!err)
		return (NULL);
	err[0] = 0;
	return (err);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	length;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	if (start > (unsigned int)length)
		return (empty());
	if (len > length - start)
		len = length - start;
	res = (char *)malloc((len + 1) * sizeof(*s));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}
