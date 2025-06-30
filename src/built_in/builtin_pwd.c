/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: matsuimiki <matsuimiki@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/27 11:58:09 by matsuimiki    #+#    #+#                 */
/*   Updated: 2025/06/30 12:19:15 by matsuimiki    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* #include "minishell.h" */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_putstr(const char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

size_t	ft_strlen(const char *str)
{
	size_t	l;

	l = 0;
	while (str[l])
	{
		l++;
	}
	return (l);
}

void	print_error(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

int ft_pwd(char **args) ////the parameter here, we need to adjust later
{
    char *cwd;

    if (count_args(args) > 1)
        return (print_error("cd: too many arguments\n"), 1);
    cwd = getcwd(NULL, 0);
    if (!cwd)
        return (perror("pwd"), 1);
    ft_putstr(cwd);
    write (STDOUT_FILENO, "\n", 1);
    free (cwd);
    return (0);
}

int main(int ac, char **av)
{
    (void)ac;
    if (av[1] && ft_strcmp(av[1], "pwd") == 0)
        ft_pwd(av);
    return(0);
}