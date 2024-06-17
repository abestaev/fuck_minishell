/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:45:40 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/06/17 16:56:41 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	get_pipe(char *str, int i, t_token *token)
{
	int	j;

	j = 0;
	token->name = malloc(2 * sizeof(char));
	if (!token->name)
		return;
	token->name[j] = str[i];
	i++;
	j++;
	token->name[j] = 0;
	token->type = PIPE;
	token->next = 0;
	return (*token);
}

t_token	get_redir_single(char *str, int i, t_token *token)
{
	int	j;

	j = 0;
	token->name = malloc(2 * sizeof(char));
	if (!token->name)
		return;
	token->name[j] = str[i];
	i++;
	j++;
	token->name[j] = 0;
	token->type = REDIRECTION;
	token->next = 0;
	return (*token);
}

t_token	get_redir_double(char *str, int i, t_token *token)
{
	int	j;

	j = 0;
	token->name = malloc(3 * sizeof(char));
	if (!token->name)
		return;
	while (j < 2)
	{
		token->name[j] = str[i];
		i++;
		j++;
	}
	token->name[j] = 0;
	token->type = REDIRECTION;
	token->next = 0;
	return (*token);
}

int is_delimitor(char *str, int i)
{
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (1);
	else if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))	
		return (1);
	return(0);
}

t_token get_word(char *str, int i, t_token *token)
{
	int j;
	int k;

	k = 0;
	j = i;
	while (str[i] && !is_delimitor(str, i))
		i++;
	token->name = malloc((i - j + 1) * sizeof(char));
	if (!token->name)
		return;
	while (k < j)
	{
		token->name[k] = str[i];
		i++;
		k++;
	}
	token->name[k] = 0;
	token->type = WORD;
	token->next = 0;
	return (*token);
}
