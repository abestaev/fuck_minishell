/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:27:27 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/29 20:11:55 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO : rajouter le vrai ft_putsrfd + changer ft_putstr_fd de void a int
int	ft_cd(t_minishell *minishell, t_command *current)
{
	char	*dir;
	char	**tab;
	t_env	*env;
	char	new_dir[2048];

	env = NULL;
	tab = current->arguments;
	if (tab && tab[0] && tab[1] && tab[2])
		return (ft_putstr_fd("too many arguments\n", 2), 1);
	if (tab && !tab[1])
		dir = match_env("HOME", minishell);
	else
		dir = tab[1];
	if (chdir(dir) == -1)
		ft_putstr_fd("cd no such file or directory\n", 2);
	if (!getcwd(new_dir, 2048))
		return (1);
	env->key = match_env("PWD", minishell);
	if (!env)
		return (0);
	free(env->value);
	env->value = ft_strdup(new_dir);
	if (!env->value)
		return (-1);
	env->next = NULL;
	return (0);
}
