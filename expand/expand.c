/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:14:03 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/09/04 16:46:25 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_expand_len(char *str, t_minishell *minishell)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i++] == '$')
		{
			if (str[i] == '?')
				len += ft_strlen(ft_itoa(minishell->exit_status));
			if (!ft_isalnumspe(str[i]))
				len++;
			else
				len += ft_env_len(str, &i, minishell);
		}
		else
			len++;
	}
	return (len + 1);
}

int	ft_expand_str(char *str, char *res, t_minishell *minishell)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i++] == '$')
		{
			if (str[i] == '?')
				ft_strncat(res, ft_itoa(minishell->exit_status), ft_strlen(ft_itoa(minishell->exit_status)));
			if (!ft_isalnumspe(str[i]))
				ft_strncat(res, str + i - 1, 1);
			else
				ft_env_expand(str, res, &i, minishell);
		}
		else
			ft_strncat(res, str + i - 1, 1);
	}
	return (0);
}

char	*handle_normal(char *str, t_minishell *minishell)
{
	int		len;
	char	*res;

	len = get_expand_len(str, minishell);
	res = malloc(len);
	if (!res)
		return (NULL);
	ft_memset(res, 0, len);
	if (ft_expand_str(str, res, minishell))
		return (free(res), NULL);
	return (res);
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
	return (res);
}
