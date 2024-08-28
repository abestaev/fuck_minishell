/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:48:45 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/28 20:08:16 by ssitchsa         ###   ########.fr       */
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

int	init_command(t_minishell *minishell, char *input)
{
	if (open_quote(input))
	{
		ft_dprintf(2, "syntax error\n");
		free(input);
		return (1);
	}
	if (tokenizer(input, minishell))
		return (printf("error tokenizer\n"), 1);
	if (!init_automate(minishell->token))
	{
		free_token(minishell->token);
		minishell->token = NULL;
		return (1);
	}
	if (parsing(minishell))
		return (printf("error parsing\n"), 1);
	print_token(minishell->token);
	free_token(minishell->token);
	minishell->token = NULL;
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_minishell	minishell;
	t_command	*tmp;

	(void)ac;
	(void)av;
	// to do: add proper initialization
	minishell = (t_minishell){0, 0, 0, 0, 0};
	if (!(isatty(1)))
		return (0);
	copy_env(env, &minishell);
	// print_env(minishell.env);
	while (1)
	{
		ft_signal();
		input = readline("\001\033[1;32m\002minishell$ \001\033[0m\002");
		if (!input)
			break ;
		if (!*input)
			continue ;
		add_history(input);
		if (init_command(&minishell, input))
			continue ;
		// gerer le quotes puis expand puis tokeniser
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
		// gestion env, TODO: deplacer dans init
		// minishell.env = NULL;
		// minishell.env_changed = FALSE;
		// copy_env(&minishell, env);
		// minishell.env_tab = env_to_tab(minishell.env);
		// minishell.path = get_path(minishell.env);
		free(input);
	}
	free_env(minishell.env);
	return (0);
}
