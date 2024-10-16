/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:40:30 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/17 20:29:14 by ssitchsa         ###   ########.fr       */
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

int	add_redirection(t_command *command, t_token *token, t_minishell *minishell)
{
	t_redir	*redirection;
	t_redir	*current;
	char	*file_name;

	redirection = malloc(sizeof(t_redir));
	if (!redirection)
		return (1);
	redirection->type = find_redir_type(token->name);
	file_name = ft_expand(token->next->name, minishell);
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

int	add_arguments(t_command *command, t_token *token, t_minishell *minishell)
{
	char	**new_arguments;
	char	*expanded;
	int		i;

	expanded = ft_expand(token->name, minishell);
	if (!expanded || !*expanded)
		return (free(expanded), !expanded);
	i = 0;
	while (command->arguments && command->arguments[i])
		i++;
	new_arguments = ft_calloc((sizeof(char *)), (i + 2));
	if (!new_arguments)
		return (1);
	if (!command->arguments)
		new_arguments[0] = expanded;
	else
	{
		i = -1;
		while (command->arguments[++i])
			new_arguments[i] = command->arguments[i];
		new_arguments[i] = expanded;
	}
	free(command->arguments);
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
	int		i;
	t_redir	*tmp;

	i = 0;
	if (command->arguments)
	{
		while (command->arguments[i])
			free(command->arguments[i++]);
		free(command->arguments);
	}
	while (command->redirections)
	{
		tmp = command->redirections->next;
		free(command->redirections->file);
		free(command->redirections);
		command->redirections = tmp;
	}
}
