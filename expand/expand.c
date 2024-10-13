/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:14:03 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/11 22:30:50 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_q_idx(char quote, int i)
{
	if (quote == '"' && i == 0)
		return (1);
	else if (quote == '\'' && i == 0)
		return (2);
	else
		return (0);
}

int	get_expand_len(char *str, t_minishell *minishell)
{
	int	i;
	int	len;
	int	q_idx;

	len = 0;
	i = 0;
	q_idx = 0;
	while (str[i])
	{
		if (str[i] == '\'' && q_idx != 2)
			q_idx = get_q_idx(str[i++], q_idx);
		else if (str[i] == '"' && q_idx != 1)
			q_idx = get_q_idx(str[i++], q_idx);
		else
		{
			if (str[i] == '$' && q_idx != 2)
				len += ft_env_len(str, &i, minishell);
			else
			{
				i++;
				len++;
			}
		}
	}
	return (len);
}

void	ft_env_expand(char *str, char *res, int *i, t_minishell *minishell)
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
		return ;
	ft_strncat(res, value, ft_strlen(value));
}

void	ft_expand_str(char *str, char *res, int *i, t_minishell *minishell)
{
	char	c;
	char	*value;
	int		start;

	if (!ft_isalpha(str[*i + 1]) && str[*i + 1] != '_')
	{
		ft_strncat(res, str + (*i)++, 1);
		return ;
	}
	start = ++(*i);
	while (ft_isalpha(str[*i]) || str[*i] == '_')
		(*i)++;
	c = str[*i];
	str[*i] = 0;
	value = match_env(str + start, minishell);
	str[*i] = c;
	if (!value)
		return ;
	ft_strncat(res, value, ft_strlen(value));
	return ;
}

char	*ft_expand(char *str, t_minishell *minishell)
{
	char	*res;
	int		i;
	int		q_idx;

	res = ft_calloc(get_expand_len(str, minishell) + 1, sizeof(char));
	if (!res)
		return (NULL);
	q_idx = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && q_idx != 2)
			q_idx = get_q_idx(str[i++], q_idx);
		else if (str[i] == '\'' && q_idx != 1)
			q_idx = get_q_idx(str[i++], q_idx);
		else
		{
			if (str[i] == '$' && q_idx != 2)
				ft_expand_str(str, res, &i, minishell);
			else
				ft_strncat(res, str + i++, 1);
		}
	}
	return (res);
}
