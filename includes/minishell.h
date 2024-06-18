/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:01:11 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/06/18 16:32:26 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_type
{
	WORD,
	PIPE,
	REDIRECTION
}					t_type;

typedef struct s_token
{
	char			*name;
	enum e_type		type;
	struct s_token	*next;
}					t_token;

typedef struct s_minishell
{
	struct s_token	**token;
}					t_minishell;

int					tokenizer(char *str, t_minishell minishell);
t_token				get_pipe(char *str, int i, t_token *token);
t_token				get_redir_single(char *str, int i, t_token *token);
t_token				get_redir_double(char *str, int i, t_token *token);
t_token				get_word(char *str, int i, t_token *token);

#endif