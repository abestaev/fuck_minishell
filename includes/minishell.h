/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:01:11 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/07/23 21:37:57 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>


typedef enum e_bool
{
	FALSE,
	TRUE
} t_bool;

typedef enum e_type
{
	WORD,
	PIPE,
	REDIRECTION
}						t_type;

typedef enum e_pety
{
	SINGLE_OUT,
	SINGLE_IN,
	DOUBLE_OUT,
	HEREDOC,
}						t_pety;

typedef struct s_token
{
	char				*name;
	t_type				type;
	struct s_token		*next;
}						t_token;

typedef struct s_redir
{
	char				*file;
	t_pety				type;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				*command;
	char				**arguments;
	t_redir				*redirections;
	struct s_command	*next;
}						t_command;

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

typedef struct s_minishell
{
	t_list				*env;
	char	**env_tab;
	bool	env_changed;
	t_token				*token;
	t_command			*command;
}						t_minishell;

int						tokenizer(char *str, t_minishell *minishell);
t_token					*get_pipe(char *str, int *i, t_token *token);
t_token					*get_redir_single(char *str, int *i, t_token *token);
t_token					*get_redir_double(char *str, int *i, t_token *token);
t_token					*get_word(char *str, int *i, t_token *token);
bool					init_automate(t_token *token);
bool					word_state(t_token *token);
bool					pipe_state(t_token *token);
bool					redir_state(t_token *token);
void					free_token(t_token *token);
int						parsing(t_minishell *minishell);
t_pety					find_redir_type(char *str);
int						add_redirection(t_command *command, t_token *token);
int						add_arguments(t_command *command, t_token *token);
void					command_add_back(t_command **command_list,
							t_command *new_command);
void					free_command(t_command *command);
void					print_tab(char **tab);
void					print_token(t_token *token);
void					print_redir(t_redir *redirection);
void					print_command(t_command *command);
t_token					*quote_word(char *str, int *i, t_token *token, char c);

// env
void	get_env(t_minishell *minishell, char **env);
t_env  *new_var(char *name, char *value);
void    print_env(t_minishell *minishell);
char    **env_to_tab(t_list *env);


#endif