/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:01:11 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/06/09 11:50:52 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

// enum Type {
// 	WORD,
// 	PIPE,
// 	REDIRECTION
// };

typedef struct token
{
	char			*name;
	// enum			type;
	struct token	*next;
}					t_token;

#endif