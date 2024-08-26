/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:30:24 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/26 20:31:01 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_negatif(char *input)
{
	int		i;
	char	j;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '"' || input[i] == '\'')
        {
			j = input[i++];
			while (input[i] != j)
			{
				input[i] = -input[i];
				i++;
			}
        }
        i++;
	}
}

void	ft_positif(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] < 0)
			input[i] = -input[i];
		i++;
	}
}