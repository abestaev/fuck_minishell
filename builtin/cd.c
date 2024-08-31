/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:27:27 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/30 23:38:02 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env(const char *key, t_minishell *minishell)
{
	t_env	*env;

	env = minishell->env;  // Assurez-vous que minishell->env est bien le point d'entrée de la liste chaînée des variables d'environnement.
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	ft_cd(t_minishell *minishell, t_command *current)
{
	char	*dir;
	char	**tab;
	t_env	*env;
	char	new_dir[2048];

	tab = current->arguments;

	if (tab && tab[0] && tab[1] && tab[2])
		return (ft_putstr_fd("too many arguments\n", 2), 1);
	if (tab && !tab[1])
		dir = match_env("HOME", minishell);
	else
		dir = tab[1];
	if (chdir(dir) == -1)
		return (ft_putstr_fd("cd: no such file or directory\n", 2), 1);
	if (!getcwd(new_dir, sizeof(new_dir)))
		return (ft_putstr_fd("cd: error getting current directory\n", 2), 1);
	env = find_env("PWD", minishell);
	if (!env)
		return (ft_putstr_fd("cd: failed to update PWD\n", 2), 1);
	free(env->value);
	env->value = ft_strdup(new_dir);
	if (!env->value)
		return (ft_putstr_fd("cd: memory allocation error\n", 2), -1);
	return (0);
}
