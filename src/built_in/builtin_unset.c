/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin_unset.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/09 10:10:55 by mmatsui        #+#    #+#                */
/*   Updated: 2025/07/09 10:10:57 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "builtin.h"

static void	delete_node(t_env *delete, t_env *prev)
{
	if (delete)
	{
		prev->next = delete->next;
		free_node(delete);
		return ;
	}
}

static void	check_delete_env(char *arg, t_env *curr, t_env *prev, t_env **envp)
{
	while (curr)
	{
		if (ft_strcmp(arg, curr->key) == 0)
		{
			if (prev == NULL)
			{
				*envp = curr->next;
				free_node (curr);
				return ;
			}
			else
				delete_node(curr, prev);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	return ;
}

int	ft_unset(char **args, t_env **envp)
{
	t_env	*curr;
	t_env	*prev;
	int		i;

	i = 0;
	while (args[i])
	{
		curr = *envp;
		prev = NULL;
		check_delete_env(args[i], curr, prev, envp);
		i++;
	}
	return (0);
}
/* ---------------------------------------------------------------- */
/* 
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

void run_test(char **args, char **envp)
{
	t_env *env_list = copy_initial_env(envp);
	if (!env_list)
		return (perror("copy_initial_env failed"), (void)0);

	
	int result = ft_unset(args + 1, &env_list);
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

	char *args1[] = {"unset", NULL};
	char *args2[] = {"unset", "PWD", NULL};
	char *args3[] = {"unset", "HOME=", NULL};
	char *args4[] = {"unset", "HOME", NULL};
	char *args5[] = {"unset", "HOME", "PWD", "OLDPWD", "BYE", "HELLO", NULL};
	

	run_test(args1, envp_mock);
	run_test(args2, envp_mock);
	run_test(args3, envp_mock);
	run_test(args4, envp_mock);
	run_test(args5, envp_mock);

    return (0);
}  */