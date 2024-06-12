/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:48:45 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/06/09 10:17:42 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char *input;
	
	while (1)
	{
		input = readline("minishell >> ");
		if (input == NULL)
			return (printf("Error readline\n"), 1);
		printf("%s\n", input);
		// tout le parsing
		// toute l'exec
		free(input);
	}
	return (0);
}


// faire un printf avec buffer 1024 j