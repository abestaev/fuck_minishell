/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:48:45 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/16 18:02:25 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	init_exec(t_minishell *minishell)
{
	t_command	*tmp;
	int			i;

	tmp = minishell->command;
	i = 0;
	while (tmp)
	{
		tmp->id = i;
		tmp->is_hd = false;
		tmp->hd_filename = NULL;
		tmp = tmp->next;
		i++;
	}
	minishell->n_cmd = i;
	return (0);
}

int	ft_exec(t_minishell *minishell, char *input)
{
	if (init_command(minishell, input))
		return (1);
	init_exec(minishell);
	if (minishell->n_cmd == 1)
		minishell->exit_status = run_single_cmd(minishell->command, minishell);
	else
		minishell->exit_status = run(minishell->command, minishell);
	signal(SIGINT, &signal_handler);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_minishell	*minishell;

	(void)ac;
	(void)av;
	minishell = starton();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &signal_handler);
	if (!(isatty(0)) || copy_env(env, minishell))
		return (0);
	while (1)
	{
		ft_signal(minishell);
		input = readline("\001\033[1;32m\002minishell$ \001\033[0m\002");
		if (!input)
			break ;
		if (!*input)
			continue ;
		add_history(input);
		if (ft_exec(minishell, input))
			continue ;
		free_all_commands(minishell);
		free(input);
	}
	return (close(minishell->old_fd[0]), close(minishell->old_fd[1]), free_env(minishell->env), 0);
}
