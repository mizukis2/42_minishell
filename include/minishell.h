/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:43:05 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/09 08:08:08 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*--------------------Libraries----------------------------*/
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <string.h>
# include <termcap.h>
# include <stdbool.h>
# include "libft.h"

/*---------------------ENUMS-------------------------------*/
/*Token type*/
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}	t_token_type;

/*Lexer_state*/
typedef enum e_lexer_state
{
	STATE_START,
	STATE_IN_WORD,
	STATE_IN_SINGLE_QUOTE,
	STATE_IN_DOUBLE_QUOTE,
	STATE_IN_METACHAR
}	t_lexer_state;

/*--------------------Structs------------------------------*/
/* Tokens */
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}				t_token;

/* Lex */
typedef struct s_lex
{
	int				i;
	int				adv;
	char			c;
	const char		*start;
	t_token			*tokens;
	t_lexer_state	state;
	t_token_type	type;
}	t_lex;

/* data struct for later*/
typedef struct s_data {
    char **copied_envp;          
    int    last_exit;     // For $?
    // maybe: char *prompt;
    // maybe: int interactive_mode;
}
	t_data;

/* envp */
typedef struct s_env {
    char    *key;
    char    *value;
    bool    exported;
    struct s_env *next;
} t_env;

/*--------------------Funtions-----------------------------*/
/* Main & shell loop */
void			enter_shell_loop(char **envp);
int				is_whitespace_or_empty(char *str);
bool			check_quotes(char *line);
bool			is_valid_input(char *line);
void			cleanup(t_token *tokens, char *line);

/* Lexer*/
t_token			*lexer(const char *line);
bool			is_metachar(char c);
t_token_type	get_metachar_type(const char *str, int *advance);
t_token			*create_token(const char *start, int len, t_token_type type);
void			add_token(t_token **head, t_token *new_token);
void			free_tokens(t_token *head);
void			process_start(t_lex *lex, const char *line);
void			process_in_inword(t_lex *lex, const char *line);
void			process_single_quotes(t_lex *lex, const char *line);
void			process_double_quotes(t_lex *lex, const char *line);


//error
void	print_error(const char *msg);

//function - environment variable
t_env	*copy_initial_env(char **envp);
t_env	*create_node(char *str);
void	free_node(t_env *node);
void	free_node_list(t_env *head);
char	**list_to_array(t_env *envp);
void	free_array (char **array);
char	*create_new_key(const char *arg);
char	*create_new_value(const char *arg);
void	update_env(const char *key, const char *path, t_env *envp);

//function - built-in, this should be impliment right parameters later
int		execute_builtin(char **args, char **envp);
int		ft_echo(char **args);
int		ft_pwd(char **args);
int		ft_env(char **args, t_env *envp);
int		ft_export(char **args, t_env *envp);
int		ft_cd(char **args, t_env *envp);
int		ft_unset(char **args, t_env **envp);

//built-in utils
int		count_args(char **args);
char	*get_env_value(t_env *envp, char *key);
void	print_error(const char *msg);

#endif