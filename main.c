/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:48:45 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/25 17:16:04 by ssitchsa         ###   ########.fr       */
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
	//to do: add proper initialization
	minishell = (t_minishell){0, 0, 0, 0, 0, 0};
	if (!(isatty(1)))
		return (0);
	while (1)
	{
		input = readline("minishell >> ");
		if (!input)
			return (0);
		if (!(*input) || open_quote(input))
		{
			if (open_quote(input))
				printf("syntax error\n");
			free(input);
			continue ;
		}
		add_history(input);
		// gerer le quotes puis expand puis tokeniser
		if (tokenizer(input, &minishell))
			return (printf("error tokenizer") ,1);
		if (!init_automate(minishell.token))
			return(free_token(minishell.token),1);
		if (parsing(&minishell))
			return (printf("error parsing") ,1);
		print_token(minishell.token);
		while (minishell.command)
		{
			// free_command(minishell.token);
			tmp = minishell.command->next;
			free(minishell.command);
			minishell.command = tmp;
		}
		minishell.token = 0;
		// toute l'exec

		// gestion env, TODO: deplacer dans init
		minishell.env = NULL;
		minishell.env_changed = FALSE;
		copy_env(&minishell, env);
		minishell.env_tab = env_to_tab(minishell.env);
		minishell.path = get_path(minishell.env);

		free(input);
	}
	return (0);
}




