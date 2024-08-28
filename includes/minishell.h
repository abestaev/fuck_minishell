/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:01:11 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/08/28 21:00:13 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}						t_bool;

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
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_minishell
{
	t_env				*env;
	char				**env_tab;
	char				**path;
	bool				env_changed;
	t_token				*token;
	t_command			*command;
}						t_minishell;

// parsing
int						tokenizer(char *str, t_minishell *minishell);
void					get_pipe(char *str, int *i, t_token *token);
void					get_redir_single(char *str, int *i, t_token *token);
void					get_redir_double(char *str, int *i, t_token *token);
void					get_word(char *str, int *i, t_token *token);
bool					init_automate(t_token *token);
bool					word_state(t_token *token);
bool					pipe_state(t_token *token);
bool					redir_state(t_token *token);
void					free_token(t_token *token);
int						parsing(t_minishell *minishell);
t_pety					find_redir_type(char *str);
int						add_redirection(t_command *command, t_token *token,
							t_minishell *minishell);
int						add_arguments(t_command *command, t_token *token,
							t_minishell *minishell);
void					command_add_back(t_command **command_list,
							t_command *new_command);
void					free_command(t_command *command);
void					print_tab(char **tab);
void					print_token(t_token *token);
void					print_redir(t_redir *redirection);
void					print_command(t_command *command);
void					quote_word(char *str, int *i, t_token *token, char c);
int						open_quote(char *str);

// env
// bool					var_exist(t_list *env, char *name);
char					**get_path(t_env *env);
int						copy_env(char **env, t_minishell *minishell);
char					**env_to_tab(t_env *env);
int						ft_envsize(t_env *env);
t_env					*ft_envnew(char *key, char *value);
void					ft_envadd_back(t_env **env, t_env *new);
void					free_tab(char **tab);
char					*match_env(char *str, t_minishell *minishell);
void					free_env(t_env *env);

// builtin
void					print_env(t_env *env);

// expand
char					*ft_expand(char *str, t_minishell *minishell);
void					ft_env_expand(char *str, char *res, int *i,
							t_minishell *minishell);
int						ft_env_len(char *str, int *i, t_minishell *minishell);
int						ft_isalnumspe(char c);


//exec
int run(t_minishell *minishell);
int exec_cmd(t_minishell *minishell);

// signal

void					ft_signal(void);

#endif