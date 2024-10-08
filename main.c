/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:48:45 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/09/04 19:02:39 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// todo fonction dans le parsing pour les quotes,
//	les retirer si elles se trouvent au milieu d'une str

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
void	print_env2(t_env *env)
{
	int	i;

	i = 0;
	while (env != 0)
	{
		printf("env numero: %d, key: %s, value: %s\n ", i, env->key,
			env->value);
		env = env->next;
		i++;
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

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_minishell	minishell;

	(void)ac;
	(void)av;
	minishell = (t_minishell){0, 0, 0, 0, 0, 0, 0, {0, 0}, {0, 0}};
	if (!(isatty(1)))
		return (0);
	if (copy_env(env, &minishell))
		return (0);
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
		init_exec(&minishell);
		if (minishell.n_cmd == 1)
			minishell.exit_status = run_single_cmd(minishell.command,
					&minishell);
		else
			minishell.exit_status = run(minishell.command, &minishell);
		free_all_commands(&minishell);
		free(input);
	}
	free_env(minishell.env);
	return (0);
}
