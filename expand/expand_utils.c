/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:30:24 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/28 00:02:31 by ssitchsa         ###   ########.fr       */
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

	j = *i;
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

void	ft_env_expand(char *str, char *res, int *i, t_minishell *minishell)
{
	int j;
	char c;
	char *value;

	j = *i;
	while (ft_isalnumspe(str[j]))
		j++;
	c = str[j];
	str[j] = 0;
	value = match_env(str + *i, minishell);
	str[j] = c;
	*i = j;
	if (!value)
		return ;
	ft_strncat(res, value, ft_strlen(value));
}
