/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:00:59 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/11 12:30:35 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_word(char *str, int *i, t_token *token, char c)
{
	int	j;
	int	k;

	k = 0;
	j = *i;
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
	(*i)++;
	token->name = malloc((*i - j + 1) * sizeof(char));
	if (!token->name)
		return ;
	while (j < *i)
		token->name[k++] = str[j++];
	token->name[k] = 0;
	token->type = WORD;
	token->next = 0;
	fprintf(stderr, "[%s] %s\n", __func__, token->name);
}

void	ft_lstadd_back(t_token **token, t_token *new)
{
	t_token	*last;

	last = *token;
	if (*token)
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
	else
		*token = new;
}

int	get_next_token(char *str, int *i, t_minishell *minishell)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (1);
	if (!ft_strncmp(str + *i, "<<", 2) || !ft_strncmp(str + *i, ">>", 2))
		get_redir_double(str, i, token);
	else if (!ft_strncmp(str + *i, "<", 1) || !ft_strncmp(str + *i, ">", 1))
		get_redir_single(str, i, token);
	else if (!ft_strncmp(str + *i, "|", 1))
		get_pipe(str, i, token);
	else
		get_word(str, i, token);
	if (!token->name)
		return (free(token), 1);
	ft_lstadd_back(&(minishell->token), token);
	return (0);
}

void	skip_whitespace(char *str, int *i)
{
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
}

int	tokenizer(char *str, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (str[i])
	{
		skip_whitespace(str, &i);
		if (!str[i])
			break ;
		if (get_next_token(str, &i, minishell))
			return (1);
	}
	return (0);
}
