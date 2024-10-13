/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:30:24 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/11 22:29:41 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnumspe(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
}

int	ft_env_len(char *str, int *i, t_minishell *minishell)
{
	int		j;
	char	c;
	char	*value;

	if (!ft_isalpha(str[*i + 1]) && str[*i + 1] != '_')
		return (++(*i), 1);
	j = ++(*i);
	while (ft_isalnumspe(str[j]))
		j++;
	c = str[j];
	str[j] = 0;
	value = match_env(str + *i, minishell);
	str[j] = c;
	*i = j;
	if (!value)
		return (0);
	return (ft_strlen(value));
}
