/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 01:30:32 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/10/14 01:32:51 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_change_value(t_env *env, char *value)
{
	char	*tmp;

	tmp = ft_strdup(value);
	if (!tmp)
		return (ft_dprintf(2, "Error malloc new env\n"), 1);
	free(env->value);
	env->value = tmp;
	return (0);
}
