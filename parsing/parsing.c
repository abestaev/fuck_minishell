/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:00:59 by pc                #+#    #+#             */
/*   Updated: 2024/09/02 19:00:16 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_parsing(t_command *command, t_token **token, t_minishell *minishell)
{
	if ((*token)->type == REDIRECTION && (*token)->next)
	{
		if (add_redirection(command, *token, minishell))
			return (1);
		*token = (*token)->next;
	}
	else if ((*token)->type == WORD)
		if (add_arguments(command, *token, minishell))
			return (1);
	*token = (*token)->next;
	return (0);
}

int	parsing(t_minishell *minishell)
{
	t_token		*token;
	t_command	*command;

	token = minishell->token;
	while (token)
	{
		command = malloc(sizeof(t_command));
		command->redirections = NULL;
		command->arguments = NULL;
		command->next = NULL;
		command->command = NULL;
		while (token && token->type != PIPE)
		{
			if (process_parsing(command, &token, minishell))
				return (1);
		}
		if (token)
			token = token->next;
		if (command->arguments)
			command->command = command->arguments[0];
		command_add_back(&minishell->command, command);
		command = NULL;
	}
	/* free_token(token); */
	return (0);
}
