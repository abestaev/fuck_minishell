/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:48:45 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/07/31 20:04:49 by albestae         ###   ########.fr       */
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

void init_env(t_minishell *minishell, char **env)
{
	minishell->env = NULL;
	minishell->env_changed = FALSE;
	copy_env(minishell, env);
	minishell->env_tab = env_to_tab(minishell->env);
	minishell->path = get_path(minishell->env);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_minishell	minishell;
	t_command	*tmp;

	(void)ac;
	(void)av;
	(void)env;
	//to do: add proper initialization
	minishell = (t_minishell){0, 0, 0, 0, 0, 0};
	if (!(isatty(1)))
		return (0);
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
		//print_command(minishell.command);
		minishell.token = 0;
		// toute l'exec

		init_env(&minishell, env);
		run(&minishell);
		// printf("commande executee\n");

		
		// free
		while (minishell.command)
		{
			free_command(minishell.command);
			tmp = minishell.command->next;
			free(minishell.command);
			minishell.command = tmp;
		}
		free(input);
	}
	return (0);
}
