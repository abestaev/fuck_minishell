/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:31:50 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/09/03 14:42:34 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env(t_minishell *minishell)
{
	t_env *tmp;

	tmp = minishell->env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	free_env(minishell->env);
	free_all_commands(minishell);
	minishell->exit_status = 0;
	exit(EXIT_SUCCESS);
}
