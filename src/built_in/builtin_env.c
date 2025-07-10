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

//#include "minishell.h"
#include "builtin.h"

int ft_env(char **args, t_env *envp)
{
	char *env_str;
	t_env *curr;

	curr = envp;
    if (count_args(args) > 1)
        return (print_error("env: too many arguments\n"), 1);
    while (curr)
    {
		if ((curr->exported && curr->value))
		{
			env_str = complete_env_line(curr);
			if (!env_str)
				return (print_error("env: memory allocation failed\n"), 1);
			ft_putstr(env_str);
			write (STDOUT_FILENO, "\n", 1);
			free(env_str);
		}
		curr = curr->next;
    }
    return (0);
}
/* void run_test(char **args, char **envp)
{
	t_env *env_list = copy_initial_env(envp);
	if (!env_list)
		return (perror("copy_initial_env failed"), (void)0);

	
	int result = ft_env(args + 1, env_list);
	printf("\nReturn: %d\nUpdated environment:\n", result);
	free_node_list(env_list);
	printf("--------------\n");
}

int main(void)
{
	char *envp_mock[] = {
		"HOME=/home/mmatsui",
		"PWD=/home/mmatsui/A_subject/minishell",
		"OLDPWD=/tmp",
		"HELLO=",
		"BYE",
		NULL
	};

	char *args1[] = {"env", NULL};
	char *args2[] = {"env", "extra_arg", NULL};
	

	run_test(args1, envp_mock);
	run_test(args2, envp_mock);

    return (0);
} */