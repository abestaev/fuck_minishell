/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojak <wojak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:55:42 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/07/26 01:56:21 by wojak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	int	i;

	i = 0;
	while (token != 0)
	{
		printf("token numero: %d, name: %s, type: %d\n ", i, token->name,
			token->type);
		token = token->next;
		i++;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i++])
		printf("	%d: %s\n", i,  tab[i]);

}

void	print_redir(t_redir *redirection)
{
	int		i;
	char	*tab[4];

	i = 0;
	tab[0] = "single_out";
	tab[1] = "single_in";
	tab[2] = "double_out";
	tab[3] = "heredoc";
	while (redirection)
	{
		printf("redirection numero: %d, type: %s, file: %s\n", i,
			tab[redirection->type], redirection->file);
		redirection = redirection->next;
		i++;
	}
}

void	print_command(t_command *command)
{
	int	i;
	t_command *tmp;
	
	i = 0;
	tmp = command;
	while (command != 0)
	{
		printf("--------------COMMAND-------------\n");
		printf("Command: %s\n", command->command);
		printf("Arguments: \n");
		print_tab(command->arguments);
		print_redir(command->redirections);
		command = command->next;
		i++;
	}
	command = tmp;
}
