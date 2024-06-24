/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:07:58 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/06/24 16:12:04 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, int size)
{
	void *new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);

	return (new_ptr);
}