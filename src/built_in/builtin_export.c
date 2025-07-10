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

//#include "minishell.h"
#include "builtin.h"

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
