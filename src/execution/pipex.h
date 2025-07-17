/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   pipex.h                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/15 14:47:50 by mmatsui        #+#    #+#                */
/*   Updated: 2025/05/22 13:59:47 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"

# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ERROR_ARG "Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n"

typedef struct s_fds
{
	int	infile;
	int	outfile;
	int	pipe_read;
	int	pipe_write;
}	t_fds;

typedef struct s_cmd
{
	char	*cmd1;
	char	*cmd2;
	char	*run_cmd;
	char	*cmd_name;
	char	*path;
	char	**args;
}	t_cmd;

void	clean_exit(t_fds *fds, const char *msg, int code);
void	free_clean_exit(char **split_list,
			t_fds *fds, const char *msg, int code);
void	ft_free_split(char **split_list);
void	init_variable(t_fds *fds, t_cmd *cmd, char **av);
char	*find_path(t_cmd *cmd, char **envp);
void	open_in_out_file(t_fds *fds, char **av);
int		pipex(int *pipefd, t_fds *fds, t_cmd *cmd, char **envp);
int		main(int ac, char **av, char **envp);

#endif
//git clone https://github.com/michmos/42_pipex_tester.git && cd 42_pipex_tester
//bash run.sh --show-valgrind
