/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:24:09 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/26 20:09:33 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// LSCOLORS=Gxfxcxdxbxegedabagacad
// key = LSCOLORS |||| value = Gxfxcxdxbxegedabagacad

int	copy_env(char **env, t_minishell *minishell)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*new_env;

	i = 0;
	while (env[i])
	{
		key = ft_substr(env[i], 0, ft_strchri(env[i], '='));
		value = ft_substr(ft_strchr(env[i], '='), 1, ft_strlen(env[i])
				- ft_strchri(env[i], '=') - 1);
		new_env = ft_envnew(key, value);
		if (!new_env)
			return (1);
		ft_envadd_back(&minishell->env, new_env);
		++i;
	}
	return (0);
}

char	**env_to_tab(t_env *env)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (ft_envsize(env) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (env)
	{
		tab[i] = ft_strjoin(env->key, "=");
		tab[i] = ft_strjoin(tab[i], env->value);
		if (!tab[i])
			return (free_tab(tab), NULL);
		env = env->next;
		++i;
	}
	tab[i] = NULL;
	return (tab);
}

char	*match_env(char *str, t_minishell *data)
{
	t_env	*current;

	if (!str || !data || !data->env)
		return (NULL);
	current = data->env;
	while (current)
	{
		if (!(ft_strcmp(str, current->key)))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
