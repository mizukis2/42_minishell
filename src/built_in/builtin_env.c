/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmatsui <mmatsui@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/27 16:26:56 by mmatsui       #+#    #+#                 */
/*   Updated: 2025/06/30 15:34:09 by mmatsui       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(char **args, t_env *envp)
{
    int i;
	char **envp_array;

    if (count_args(args) > 2)
        return (print_error("env: too many arguments\n"), 1);
    i = 0;

	envp_array = list_to_array(envp);

    while (envp)
    {
		if (envp->value)

        if (ft_strchr(envp_array[i], '='))
        {
            ft_putstr(envp_array[i]);
            write (STDOUT_FILENO, "\n", 1);
        }
        i++;
    }
    return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void run_test(char **args, char **envp)
{
	char **copy_envp = env_dup(envp);
	if (!copy_envp)
		return (perror("env_dup failed"), (void)0);
	
	int result = ft_env(args, &copy_envp);
	printf("\nReturn: %d\nUpdated environment:\n", result);
	free_array(copy_envp);
	printf("--------------\n");
}

int main(void)
{
	char *envp_mock[] = {
		"HOME=/home/mmatsui",
		"PWD=/home/mmatsui/A_subject/minishell",
		"OLDPWD=/tmp",
		NULL
	};

	char *args1[] = {"env", NULL};
	char *args2[] = {"env", "~", NULL};

	run_test(args1, envp_mock);
	run_test(args2, envp_mock);
    run_test(args1, NULL);

    return (0);
}