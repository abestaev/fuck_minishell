/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:01:11 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/06/20 23:19:20 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef enum e_type
{
	WORD,
	PIPE,
	REDIRECTION
}					t_type;

typedef	enum e_pety
{
	SINGLE_OUT,
	SINGLE_IN,
	DOUBLE_OUT,
	HEREDOC,
}					t_pety;

typedef struct s_token
{
	char			*name;
	t_type			type;
	struct s_token	*next;
}					t_token;

typedef	struct s_redir
{
	char *file;
	t_pety	type;
	struct s_redir	*next;
}	t_redir;

typedef	struct s_command
{
	char	*command;
	char	**arguments;
	struct t_redir	*redirections;
	struct s_command *next;
}	t_command;

typedef struct s_minishell
{
	struct s_token	*token;
	struct s_command *command;
}					t_minishell;

int					tokenizer(char *str, t_minishell *minishell);
t_token				*get_pipe(char *str, int *i, t_token *token);
t_token				*get_redir_single(char *str, int *i, t_token *token);
t_token				*get_redir_double(char *str, int *i, t_token *token);
t_token				*get_word(char *str, int *i, t_token *token);
bool 				init_automate(t_token *token);
bool word_state(t_token *token);
bool pipe_state(t_token *token);
bool redir_state(t_token *token);
void free_token(t_token *token);

#endif