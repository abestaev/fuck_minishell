/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:27:27 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/25 15:24:41 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO : rajouter le vrai ft_putsrfd + changer ft_putstr_fd de void a int
// int	ft_cd(t_minishell *mini, t_command *current)
// {
// 	char	*dir;
// 	char	**tab;
// 	t_env	*env;
// 	char	new_dir[2048];

// 	tab = current->arguments;
// 	if (tab && tab[0] && tab[1] && tab[2])
// 		return (ft_putstr_fd("too many arguments\n", 2));
// 	if (tab && !tab[1])
// 		dir = match_env("HOME", mini);
// 	else
// 		dir = tab[1];
// 	if (chdir(dir) == -1)
// 		putstr_fd("cd no such file or directory\n", 2);
// 	if (!getcwd(new_dir, 2048))
// 		return (1);
// 	env = match_env("PWD", mini);
// 	if (!env)
// 		return (0);
// 	free(env->value);
// 	env->value = ft_strdup(new_dir);
// 	if (!env->value)
// 		return (-1);
// 	return (0);
// }
