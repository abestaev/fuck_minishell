/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:14:03 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/26 21:26:43 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_expand_len(char *str, t_minishell *minishell)
{
	int	i;
	int len;
	int j;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i++] == '$')
		{
			if (!ft_isalnumspe(str[i]))
				len++;
			else
			{
				j = 0;

			}
		}
		else
			len++;
	}
}

char	*handle_normal(char *str, t_minishell *minishell)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i])
	{
		
	}
}

char	*ft_expand(char *str, t_minishell *minishell)
{
	char *res;

	if (!str || !*str)
		return (str);

	if (*str == '\'')
		res = ft_substr(str, 1, ft_strlen(str) - 2);
	else
	{
		if (*str == '"')
		{
			str[ft_strlen(str) - 1] = 0;
			res = handle_normal(str + 1, minishell);
		}
		else
			res = handle_normal(str, minishell);
	}
	if (!res)
		return (NULL);
	// free(str);
	return (res);
}