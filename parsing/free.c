/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:55:07 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/15 15:12:41 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->name);
		free(token);
		token = tmp;
	}
}

void	free_all_commands(t_minishell *minishell)
{
	t_command	*tmp;

	while (minishell->command)
	{
		if (minishell->command->hd_filename)
			free(minishell->command->hd_filename);
		free_command(minishell->command);
		tmp = minishell->command->next;
		free(minishell->command);
		minishell->command = tmp;
	}
}
