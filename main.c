/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:48:45 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/06/22 01:49:47 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	int	i;

	i = 0;
	while (token != 0)
	{
		printf("token numero: %d, name: %s, type: %d\n ", i, token->name,
			token->type);
		token = token->next;
		i++;
	}
}

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

	(void)ac;
	(void)av;
	(void)env;
	minishell = (t_minishell){0, 0};
	while (1)
	{
		input = readline("minishell >> ");
		if (input == NULL)
			return (printf("Error readline\n"), 1);
		tokenizer(input, &minishell);
		print_token(minishell.token);
		// tout le parsing
		// toute l'exec
		free(input);
	}
	free_token(minishell.token);
	return (0);
}
