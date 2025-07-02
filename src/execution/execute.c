/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   execute.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/12 13:22:17 by mmatsui        #+#    #+#                */
/*   Updated: 2025/06/12 13:22:18 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
memo :
if (is_builtin(cmd->args[0]))
    execute_builtin(cmd, &data); // execute build in 
else
    fork_and_exec(cmd, &data); // execute other commands

	if the commands are not found in buildin selection and fork_exec ones, fail?
	maybe not found this command, like that?
 */