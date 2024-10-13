/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:45:40 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/13 17:32:51 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pipe(char *str, int *i, t_token *token)
{
	int	j;

	j = 0;
	token->name = malloc(2 * sizeof(char));
	if (!token->name)
		return ;
	token->name[j] = str[*i];
	(*i)++;
	token->name[++j] = 0;
	token->type = PIPE;
	token->next = 0;
}

void	get_redir_single(char *str, int *i, t_token *token)
{
	int	j;

	j = 0;
	token->name = malloc(2 * sizeof(char));
	if (!token->name)
		return ;
	token->name[j] = str[*i];
	(*i)++;
	token->name[++j] = 0;
	token->type = REDIRECTION;
	token->next = 0;
}

void	get_redir_double(char *str, int *i, t_token *token)
{
	int	j;

	j = 0;
	token->name = malloc(3 * sizeof(char));
	if (!token->name)
		return ;
	while (j < 2)
	{
		token->name[j++] = str[*i];
		(*i)++;
	}
	token->name[j] = 0;
	token->type = REDIRECTION;
	token->next = 0;
}

int	get_len_word(char *input, int i)
{
	int		len;
	char	quote;

	len = 0;
	while (input[i] && !is_delimitor(input, i))
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i];
			len++;
			while (input[++i] != quote)
			{
				len++;
			}
			len++;
		}
		len++;
		i++;
	}
	return (len);
}

void	get_word(char *str, int *i, t_token *token)
{
	int	j;

	token->name = malloc((get_len_word(str, *i) + 1) * sizeof(char));
	if (!token->name)
		return ;
	j = 0;
	while (str[*i] && !is_delimitor(str, *i))
	{
		if (str[*i] == '"' || str[*i] == '\'')
			cat_quotes(token->name, str, &j, i);
		else
			token->name[j++] = str[(*i)++];
	}
	token->name[j] = 0;
	token->type = WORD;
	token->next = 0;
}
