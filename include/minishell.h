/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:43:05 by zekhatib          #+#    #+#             */
/*   Updated: 2025/08/06 09:13:03 by zekhatib         ###   ########.fr       */
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
# include <fcntl.h>
# include "libft.h"

/*----------------------Colors-----------------------------*/
# define RED     "\033[31m"
# define PURPLE "\e[0;35m"
# define RESET   "\033[0m"

/*---------------------DIFINE-------------------------------*/
//this used for s_exec struct
# define MAX_CMDS 100

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

/* Parser */
typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	bool			append;
	bool			heredoc;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_heredoc
{
	char			*clean_delim;
	char			*temp_path;
	int				fd;
	bool			is_quoted;
}	t_heredoc;

/* Expansion */
typedef struct s_expander
{
	char			*result;
	int				i;
	bool			in_single_quote;
	bool			in_double_quote;
}	t_expander;

/* Environment Variables */
typedef struct s_env
{
	char			*key;
	char			*value;
	bool			exported;
	struct s_env	*next;
}	t_env;

typedef struct s_exec
{
	int				prev_pipe_read;
	int				curr_pipe[2];
	pid_t			pids[MAX_CMDS];
	int				num_pids;
	pid_t			last_pid;
	int				status;
}	t_exec;

/* Shell */
typedef struct s_shell
{
	char			*line;
	t_token			*tokens;
	t_cmd			*commands;
	t_env			*env_list;
	t_exec			exec;
	int				last_exit_code;
}	t_shell;
/*--------------------Funtions-----------------------------*/
/* Main & shell loop */
void			start_shell(char **envp);
bool			is_valid_input(t_shell *shell);
void			cleanup(t_shell *shell);

/* Lexer */
bool			tokenize_input(t_shell *shell);
t_token			*lexer(char *line);
void			lexer_init(t_lex *lex, char *line);

/* Lexer Utils */
bool			is_metachar(char c);
t_token_type	get_metachar_type(char *str, int *advance);
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
bool			parse_tokens(t_shell *shell);
char			**argslst_to_array(t_list *args);
void			free_cmd_list(t_cmd *cmd);
void			free_cmd_and_args(t_cmd *cmd, t_list *args);

/* Parse types */
t_cmd			*parse_command(t_shell *shell, t_token **tokens);
void			parse_word(t_token **tokens, t_list **args,
					t_cmd *cmd, t_shell *shell);
void			parse_redirect_in(t_token **tokens, t_list **args,
					t_cmd *cmd, t_shell *shell);
void			parse_redirect_o(t_token **tokens, t_list **args,
					t_cmd *cmd, t_shell *shell);
void			parse_heredoc(t_token **tokens, t_list **args,
					t_cmd *cmd, t_shell *shell);

/* Heredoc */					
void			collect_heredoc(int fd, char *delim,
					bool is_quoted, t_shell *shell);
int				create_temp_heredoc(char **out_path);
char			*create_heredoc_file(const char *delim, t_shell *shell);

/* Expansion */
char			*expand_variables(const char *value, t_shell *shell);
int				var_len(const char *s);
void			append_to_result(char **result, char *str);
void			append_char_to_result(char **result, char c);

/* Error */
void			print_error(const char *msg);

/* function - environment variable */
t_env			*copy_initial_env(char **envp);
t_env			*create_node(char *str);
void			free_node(t_env *node);
void			free_node_list(t_env *head);
char			**list_to_array(t_env *envp);
void			free_array(char **array);
char			*create_new_key(const char *arg);
char			*create_new_value(const char *arg);
void			update_env(const char *key, const char *path, t_env *envp);
char			*complete_env_line(t_env *envp);
int				count_nodes(t_env *head);

/* function - built-in*/
int				execute_builtin(char **args, t_env *env_list);//
int				execute_builtin_exit(t_shell *shell, int save_in, int save_out);
int				ft_echo(char **args);
int				ft_pwd(char **args);
int				ft_env(char **args, t_env *envp);
void			print_all_list(t_env *env_list);
int				ft_export(char **args, t_env *envp);
int				ft_cd(char **args, t_env *envp);
int				ft_unset(char **args, t_env **envp);
int				ft_exit(t_shell *shell, int save_in, int save_out);

/* built-in utils */
int				count_args(char **args);
char			*get_env_value(t_env *envp, char *key);
void			print_error_builtin(const char *msg); //this and other "print_error should be one?"

/* executon */
void			run_execution(t_shell *shell);
void			free_split(char **split_list);
void			cleanup_child(t_shell *shell);
void			clean_exit(t_shell *shell, const char *msg,
					char *cmd, int code);
void			execute_command(char **argv, t_shell *shell);
bool			is_builtin(char **argv);
bool			run_in_parent(char **argv);
int				execute(t_shell *shell);
void			clean_shell(t_shell *shell);
void			restore_std_close_fd(int save_in, int save_out);
bool			set_redirection_pipe(t_cmd *curr_cmd, t_exec *exec);
void			waitpid_loop(t_exec *exec);
void			init_exec(t_exec *exec);
int				run_builtin_parent(t_cmd *commands, t_shell *shell);

#endif