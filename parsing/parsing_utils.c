/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:40:30 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/07/20 12:48:05 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pety	find_redir_type(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (DOUBLE_OUT);
	if (!ft_strncmp(str, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(str, ">", 1))
		return (SINGLE_OUT);
	return (SINGLE_IN);
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
	file_name = ft_strdup(token->next->name);
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
	new_arguments = malloc((i + 2) * sizeof(char *));
	if (!new_arguments)
		return (1);
	if (!command->arguments)
		new_arguments[0] = ft_strdup(token->name);
	else
	{
		i = -1;
		while (command->arguments[++i])
			new_arguments[i] = command->arguments[i];
		new_arguments[i] = ft_strdup(token->name);
	}
	if (!new_arguments[i])
		return (1);
	// new_arguments[i + 1] = NULL;
	command->arguments = new_arguments;
	return (0);
}

void	command_add_back(t_command **command_list, t_command *new_command)
{
	t_command	*current;

	if (!command_list || !new_command)
		return ;
	if (!*command_list)
	{
		*command_list = new_command;
		return ;
	}
	current = *command_list;
	while (current->next)
		current = current->next;
	current->next = new_command;
}

void	free_command(t_command *command)
{
	int	i;

	i = 0;
	if (command->arguments)
	{
		while (command->arguments[i])
			free(command->arguments[i++]);
		free(command->arguments);
	}
	free(command->redirections);
}
