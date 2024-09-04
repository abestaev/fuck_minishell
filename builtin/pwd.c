/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:01:41 by albestae          #+#    #+#             */
/*   Updated: 2024/09/03 21:01:58 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_minishell *minishell)
{
    char	*pwd;

    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        perror("getcwd failed\n");
        minishell->exit_status = 1;
        return (EXIT_FAILURE);
    }
    ft_putstr_fd(pwd, 1);
    ft_putstr_fd("\n", 1);
    free(pwd);
    minishell->exit_status = 0;
    return (EXIT_SUCCESS);
}