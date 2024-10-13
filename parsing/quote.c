/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:05:07 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/11 22:42:54 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*retirerquote(char *str)
{
	int		i;
	int		n;
	char	*new;
	char	c;

	i = 0;
	n = 0;
	new = malloc(strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				new[n++] = str[i++];
			i++;
		}
		if (str[i])
			new[n++] = str[i++];
	}
	new[n] = '\0';
	free(str);
	return (new);
}

int	open_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] != quote)
				return (1);
		}
		i++;
	}
	return (0);
}

void	cat_quotes(char *name, char *input, int *j, int *i)
{
	char	quote;

	quote = input[(*i)++];
	name[(*j)++] = quote;
	while (input[*i] != quote)
		name[(*j)++] = input[(*i)++];
	name[(*j)++] = input[(*i)++];
}

int	is_delimitor(char *str, int i)
{
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (1);
	if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		return (1);
	return (0);
}
