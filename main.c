/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojak <wojak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:48:45 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/07/26 02:22:49 by wojak            ###   ########.fr       */
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
	// t_command	*tmp;

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

		// gestion env, TODO: deplacer dans init
		minishell.env = NULL;
		minishell.env_changed = FALSE;
		copy_env(&minishell, env);
		minishell.env_tab = env_to_tab(minishell.env);
		minishell.path = get_path(minishell.env);

		// test exec
		pid_t pid;
		pid = fork();
		if (pid == 0)
			exec_cmd(&minishell);
		// printf("commande executee\n");
		// free
		// while (minishell.command)
		// {
		// 	free_command(minishell.command);
		// 	tmp = minishell.command->next;
		// 	free(minishell.command);
		// 	minishell.command = tmp;
		// }
		free(input);
	}
	return (0);
}
