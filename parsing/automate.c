/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:10:49 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/06/22 01:49:38 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft init qu'on appelle dans le main
bool	init_automate(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == WORD)
		return (word_state(token->next));
	if (token->type == REDIRECTION)
		return (redir_state(token->next));
	else
		return (0);
}

bool	word_state(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == WORD)
		return (word_state(token->next));
	if (token->type == REDIRECTION)
		return (redir_state(token->next));
	if (token->type == PIPE)
		return (pipe_state(token->next));
	else
		return (0);
}

bool	pipe_state(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == WORD)
		return (word_state(token->next));
	if (token->type == REDIRECTION)
		return (redir_state(token->next));
	else
		return (0);
}

bool	redir_state(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == WORD)
		return (word_state(token->next));
	else
		return (0);
}
