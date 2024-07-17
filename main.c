/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:48:45 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/07/17 18:00:56 by ssitchsa         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_minishell	minishell;
	t_command	*tmp;

	(void)ac;
	(void)av;
	(void)env;
	minishell = (t_minishell){0, 0};
	while (1)
	{
		input = readline("minishell >> ");
		if (input == NULL)
			return (0);
		if (!(*input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		tokenizer(input, &minishell);
		parsing(&minishell);
		print_command(minishell.command);
		while (minishell.command)
		{
			free_command(minishell.command);
			tmp = minishell.command->next;
			free(minishell.command);
			minishell.command = tmp;
		}
		minishell.token = 0;
		// toute l'exec
		free(input);
	}
	return (0);
}
