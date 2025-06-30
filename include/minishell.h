/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:43:05 by zekhatib          #+#    #+#             */
/*   Updated: 2025/06/30 04:19:39 by zekhatib         ###   ########.fr       */
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

//struct

//funtions - main / shell loop
void	shell_loop(void);
int		is_whitespace_or_empty(char *str);
bool	check_quotes(char *line);
void	cleanup_shell(void);

//function - initial setting
char	**env_dup(char **envp);

//function - utils (minishell libft)
void	ft_putstr(const char *str);
int		ft_strcmp(const char *s1, const char *s2);

//function - build-in, this should be impliment right parameters later
int	buid_in(char **args); 
void	ft_echo(char **args);


#endif