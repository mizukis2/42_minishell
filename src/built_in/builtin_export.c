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
	print_error_builtin("export: `");
	print_error_builtin(arg);
	print_error_builtin("': not a valid identifier\n");
}

static int	build_new_env(char *item, t_env *env_list)
{
	char	*new_key;
	char	*new_value;

	new_key = create_new_key(item);
	if (!new_key)
		return (1);
	new_value = create_new_value(item);
	update_env(new_key, new_value, env_list);
	free(new_key);
	free(new_value);
	return (0);
}

int	ft_export(char **args, t_env *env_list)
{
	int		i;
	int		exit_code;

	if (args[0] == NULL)
		return (print_all_list(env_list), 0);
	i = 0;
	exit_code = 0;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
		{
			if (build_new_env(args[i], env_list) != 0)
				exit_code = 1;
		}
		else
		{
			print_identifier_error(args[i]);
			exit_code = 1;
		}
		i++;
	}
	return (exit_code);
}
