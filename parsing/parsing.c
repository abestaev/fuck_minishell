/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:00:59 by pc                #+#    #+#             */
/*   Updated: 2024/07/20 12:27:31 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_parsing(t_command *command, t_token **token)
{
	if ((*token)->type == REDIRECTION)
	{
		if (add_redirection(command, *token))
			return (1);
		*token = (*token)->next;
	}
	else if ((*token)->type == WORD)
		if (add_arguments(command, *token))
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
			if (process_parsing(command, &token))
				return (1);
		}
		if (token)
			token = token->next;
		if (command->arguments)
			command->command = command->arguments[0];
		command_add_back(&minishell->command, command);
		command = NULL;
	}
	// free_token(token);
	return (0);
}

/*
t'as juste a ecrire les fonctions add_redirections et add_arguments
et cest tout bon
apres ca le parsing est fini

ls -l -R -a | wc -l

arguments = ["ls", "-l", "-R", "-a"]

*/