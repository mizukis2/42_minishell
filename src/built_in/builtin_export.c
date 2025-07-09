/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin_export.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/02 09:34:22 by mmatsui        #+#    #+#                */
/*   Updated: 2025/07/02 09:34:23 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_identifier(const char *arg)
{
	int	i;
	if (!arg || (!(ft_isalpha(arg[0]) || arg[0] == '_')))
		return (false);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalnum(arg[i]) || (arg[i] == '_')))
			return (false);
		i++;
	}
	return (true);
}

static void	print_identifier_error(const char *arg)
{
	write (STDERR_FILENO, "export: `", 10);
	write (STDERR_FILENO, arg, ft_strlen(arg));
	write (STDERR_FILENO, "': not a valid identifier\n", 27);
}

static void	print_all_list(t_env *envp)
{
	t_env	*curr;
	
	curr = envp;
	while (curr)
	{
		write (STDOUT_FILENO, "declare -x ", 11);
		ft_putstr(curr->key);
		if (curr->exported && curr->value)
		{
			write (STDOUT_FILENO, "=\"", 2);
			ft_putstr(curr->value);
			write (STDOUT_FILENO, "\"", 1);
		}
		write (STDOUT_FILENO, "\n", 1);
		curr = curr->next;
	}
}

int	ft_export(char **args, t_env *envp)
{
	int		i;
	char	*new_key;
	char	*new_value;

	if (args[0] == NULL)
		return (print_all_list(envp), 0);
	i = 0;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
		{
			new_key = create_new_key(args[i]);
			if (!new_key)
				return (1);
			new_value = create_new_value(args[i]);
			update_env(new_key, new_value, envp);
			free(new_key);
			free(new_value);
		}
		else
			print_identifier_error(args[i]);
		i++;
	}
	return (0);
}
/* 
void run_test(char **args, char **envp)
{
	t_env *env_list = copy_initial_env(envp);
	if (!env_list)
		return (perror("copy_initial_env failed"), (void)0);

	
	int result = ft_export(args + 1, env_list);
	printf("\nReturn: %d\nUpdated environment:\n", result);
	print_all_list(env_list);
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

	//char *args1[] = {"export", NULL};
	char *args2[] = {"export", "TEST1=hello", NULL};
	char *args3[] = {"export", "TEST2", NULL};
	char *args4[] = {"export", "TEST3=", NULL};
	//char *args5[] = {"export", "_TEST4=bye", NULL};
	//char *args6[] = {"export", "5TEST=error", NULL};
	//char *args7[] = {"export", "TEST1=", "TEST2","TEST3=hello", NULL};
	//char *args8[] = {"export", "", NULL};                 // empty string
	//char *args9[] = {"export", "TEST5=abc=def", NULL};    // multiple '='
	//char *args10[] = {"export", "HOME=/this/is/new", NULL};
	

	//run_test(args1, envp_mock);
	run_test(args2, envp_mock);
	run_test(args3, envp_mock);
	run_test(args4, envp_mock);
	//run_test(args5, envp_mock);
	//run_test(args6, envp_mock);
	//run_test(args7, envp_mock);
	//run_test(args8, envp_mock);
	//run_test(args9, envp_mock);
	//run_test(args10, envp_mock);

    return (0);
} */

