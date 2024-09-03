/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:23:53 by albestae          #+#    #+#             */
/*   Updated: 2024/09/03 14:29:34 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_name(void)
{
	static int	i;
	char		*filename;
	char		*num;

	i = 0;
	num = ft_itoa(i++);
	if (!num)
	{
		perror("itoa failed\n");
		return (NULL);
	}
	filename = ft_strjoin("/tmp/heredoc_", num);
	if (!filename)
	{
		perror("strjoin failed\n");
		return (NULL);
	}
	free(num);
	ft_putstr_fd(num, 2);
	return (filename);
}

// int read_heredoc(t_command *command, t_minishell *minishell)
// {
//     // creer fichier tmp

//     // while (1)

//     // line = read line
//     // putstr fd line dans fichier tmp

//     // dup2 fichier tmp dans STDIN_FILENO
//     // close fd et unlink tmp

// }