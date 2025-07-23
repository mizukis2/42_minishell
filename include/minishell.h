/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:43:05 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/23 03:58:08 by zekhatib         ###   ########.fr       */
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

/*Quote Type*/
typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote_type;

/*--------------------Structs------------------------------*/
/* Tokens */
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote_type	quote_type;
	struct s_token	*next;
}	t_token;

/* Lex */
typedef struct s_lex
{
	int				i;
	int				adv;
	char			c;
	char			*line;
	char			*start;
	t_token			*tokens;
	t_token			*new_token;
	t_lexer_state	state;
	t_token_type	type;
}	t_lex;

/*--------------------Funtions-----------------------------*/
/* Main & shell loop */
void			enter_shell_loop(char **envp);
int				is_whitespace_or_empty(char *str);
bool			check_quotes(char *line);
bool			is_valid_input(char *line);
void			cleanup(t_token *tokens, char *line);

/* Lexer */
t_token			*tokenize_input(char *line);
t_token			*lexer(char *line);
void			lexer_init(t_lex *lex, char *line);

/* Lexer Utils */
bool			is_metachar(char c);
t_token_type	get_metachar_type(char *str, int *advance);
bool			strip_quotes(char **old);
bool			set_quotes(t_token *tokens);
bool			syntax_check(t_token *tokens);

/* Lexer States */
void			process_start(t_lex *lex, char *line);
void			process_inword(t_lex *lex, char *line);
void			process_single_quotes(t_lex *lex, char *line);
void			process_double_quotes(t_lex *lex, char *line);

/* Token Utils */
t_token			*create_token(char *start, int len, t_token_type type);
void			add_token(t_token **head, t_token *new_token);
void			free_tokens(t_token *head);
bool			should_make_token(t_lex *lex, char *line);
bool			make_token(t_lex *lex, int len, t_token_type type);

/* Parser */
t_cmd			*parse_tokens(t_token *tokens);
t_cmd			*parse_command(t_token **tokens);
char			**argslst_to_array(t_list *args);
void			free_cmd_list(t_cmd *cmd);
t_cmd			*free_and_error(t_cmd *cmd, t_list *args);

/* Parse types */
void			parse_word(t_token **tokens, t_list **args, t_cmd *cmd);
void			parse_redirect_in(t_token **tokens, t_list **args, t_cmd *cmd);
void			parse_redirect_o(t_token **tokens, t_list **args, t_cmd *cmd);
void			parse_heredoc(t_token **tokens, t_list **args, t_cmd *cmd);

//error
void			print_error(const char *msg);

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
int				count_args(char **args);
char			*get_env_value(t_env *envp, char *key);
void			print_error(const char *msg);

#endif