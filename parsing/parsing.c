/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:00:59 by pc                #+#    #+#             */
/*   Updated: 2024/06/24 16:09:53 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pety	find_redir_type(char *str)
{
	if (!ft_strncmp(str, ">", 1))
		return (SINGLE_OUT);
	else if (!ft_strncmp(str, "<", 1))
		return (SINGLE_IN);
	else if (!ft_strncmp(str, ">>", 2))
		return (DOUBLE_OUT);
	else
		return (HEREDOC);
}

int	add_redirection(t_command *command, t_token *token)
{
	t_redir	*redirection;
	t_redir	*current;
	char	*file_name;

	redirection = malloc(sizeof(t_redir));
	if (!redirection)
		return (1);
	redirection->type = find_redir_type(token->name);
	token = token->next;
	file_name = ft_strdup(token->name);
	if (!file_name)
		return (free(redirection), 1);
	redirection->file = file_name;
	redirection->next = NULL;
	if (command->redirections == NULL)
		command->redirections = redirection;
	else
	{
		current = command->redirections;
		while (current->next != NULL)
			current = current->next;
		current->next = redirection;
	}
	return (0);
}

int	add_arguments(t_command *command, t_token *token)
{
	char	**new_arguments;
	int		i;

	i = 0;
	while (command->arguments && command->arguments[i] != NULL)
		i++;
	new_arguments = ft_realloc(command->arguments, (i + 2) * sizeof(char *));
	if (!new_arguments)
		return (1);
	new_arguments[i] = strdup(token->name);
	if (!new_arguments[i])
		return (1);
	new_arguments[i + 1] = NULL;
	command->arguments = new_arguments;
	return (0);
}

int	parsing(t_minishell *minishell)
{
	t_token		*token;
	t_command	*command;

	// tu vas loop sur les tokens jusqua que tu trouves un pipe
	// tu vas creer une commande,
	//	et tu vas ajouter au fur et a mesure les redirections et les arguments de la commande
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