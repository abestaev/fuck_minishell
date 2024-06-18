/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:48:45 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/06/18 16:33:30 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	int	i;

	i = 0;
	while (token->next != 0)
	{
		printf("token numero: %d, name: %s, type: %d\n ", i, token->name,
			token->type);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_minishell	minishell;

	(void)ac;
	(void)av;
	(void)env;
	minishell = (t_minishell){0};

	while (1)
	{
		input = readline("minishell >> ");
		if (input == NULL)
			return (printf("Error readline\n"), 1);
		tokenizer(input, minishell);
		// tout le parsing
		// toute l'exec
		free(input);
	}
	return (0);
}
