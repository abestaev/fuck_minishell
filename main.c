/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:48:45 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/09/02 14:01:45 by albestae         ###   ########.fr       */
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
		free_command(minishell->command);
		tmp = minishell->command->next;
		free(minishell->command);
		minishell->command = tmp;
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
	free_token(minishell->token);
	minishell->token = NULL;
	return (0);
}

// void	init_env(t_minishell *minishell, char **env)
// {
// 	if (copy_env(env, minishell))
// 		return ;
// 	minishell->env_tab = env_to_tab(minishell->env);
// 	minishell->path = get_path(minishell->env);
// }

static int init_exec(t_minishell *minishell)
{	
	t_command *tmp = minishell->command;
	int i = 0;
	while (tmp)
	{
		tmp->id = i;
		tmp = tmp->next;
		i++;
	}
	minishell->n_cmd = i;
	return (0);
}
int	main(int ac, char **av, char **env)
{
	char		*input;
	t_minishell	minishell;

	(void)ac;
	(void)av;
	// to do: add proper initialization
	minishell = (t_minishell){0, 0, 0, 0, 0, 0, 0, {0, 0}, {0, 0}};
	if (!(isatty(1)))
		return (0);
	if (copy_env(env, &minishell))
		return (0);
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
		// print_command(minishell.command);
		init_exec(&minishell);
		run(minishell.command, &minishell);
		// free
		free_all_commands(&minishell);
		// minishell.token = 0;
		free(input);
	}
	free_env(minishell.env);
	return (0);
}
