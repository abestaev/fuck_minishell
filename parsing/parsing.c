/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:00:59 by pc                #+#    #+#             */
/*   Updated: 2024/06/20 23:19:49 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parsing(t_minishell *minishell)
{
	// tu vas loop sur les tokens jusqua que tu trouves un pipe
	// tu vas creer une commande, et tu vas ajouter au fur et a mesure les redirections et les arguments de la commande
	t_token *token;
	t_command *command;

	token = minishell->token;
	while (token) 
	{   
		command = malloc(sizeof(t_command)); // init la commande
		command->redirections = NULL;
		command->arguments = NULL;
		while (token && token->type != PIPE)
        {
			if (token->type == REDIRECTION)
				if (add_redirections(command, token))
					return (1);
			if (token->type == WORD)
				if (add_arguments(command, token))
					return (1);
			token = token->next;
        }
		if (token)
			token = token->next;
		command->command = command->arguments[0];
		command_add_back(minishell->command, command);
		command = NULL;
	}
}

/*
t'as juste a ecrire les fonctions add_redirections et add_arguments
et cest tout bon
apres ca le parsing est fini

ls -l -R -a | wc -l

arguments = ["ls", "-l", "-R", "-a"]

*/