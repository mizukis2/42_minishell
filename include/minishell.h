/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:43:05 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/02 11:08:13 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//libraries
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

	
//Error messages

//---------------------ENUMS-------------------------------
//Token type
typedef enum	e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}				t_token_type;

//Lexer_state
typedef enum	e_lexer_state
{
	STATE_START,
	STATE_IN_WORD,
	STATE_IN_SINGLE_QUOTE,
	STATE_IN_DOUBLE_QUOTE,
	STATE_IN_METACHAR
}				t_lexer_state;

//--------------------Structs------------------------------
//Tokens
typedef struct	s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}				t_token;


//--------------------Funtions-----------------------------
//main & shell loop
void			enter_shell_loop(void);
int				is_whitespace_or_empty(char *str);
bool			check_quotes(char *line);
void			cleanup_shell(void);

// Lexer
t_token			*lexer(const char *line);
bool			is_metachar(char c);
t_token_type	get_metachar_type(const char *str, int *advance);
t_token			*create_token(const char *start, int len, t_token_type type);
void			add_token(t_token **head, t_token *new_token);
void			free_tokens(t_token *head);


//function - initial setting
char	**env_dup(char **envp);

//function - utils (minishell libft)
void	ft_putstr(const char *str);
int		ft_strcmp(const char *s1, const char *s2);

//function - build-in, this should be impliment right parameters later
int	buid_in(char **args); 
void	ft_echo(char **args);


#endif