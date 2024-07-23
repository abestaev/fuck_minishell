/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:48:45 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/07/23 21:50:16 by albestae         ###   ########.fr       */
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
	minishell = (t_minishell){0, 0, 0};
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
		while (minishell.command)
		{
			free_command(minishell.command);
			tmp = minishell.command->next;
			free(minishell.command);
			minishell.command = tmp;
		}
		minishell.token = 0;
		// toute l'exec

		// gestion env, a deplacer dans init aussi 
		
		minishell.env = NULL;	//to do: deplacer dans init
		get_env(&minishell, env);
		print_env(&minishell);
		
		free(input);
	}
	return (0);
}
void	get_env(t_minishell *minishell, char **env)
{
	int			i;
	int 		j;
	t_list	*tmp_lst = NULL;
	t_env 	*tmp_var;
	
	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		tmp_var = new_var(ft_substr(env[i], 0, j), 
			ft_substr(env[i], j + 1, (ft_strlen(env[i]) - j - 1)));
		tmp_lst = ft_lstnew(tmp_var);
		if (minishell->env)
			ft_lstadd_back_2(&minishell->env, tmp_lst);
		else
			minishell->env = tmp_lst;
		i++;
	}
}



t_env  *new_var(char *name, char *value)
{
	t_env *var;

	if (!name || !value)
        return (NULL);
	var = malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->name = name;
	var->value = value;
	return (var);
}
