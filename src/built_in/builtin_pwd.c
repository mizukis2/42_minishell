/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmatsui <mmatsui@student.codam.nl            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/27 11:58:09 by mmatsui       #+#    #+#                 */
/*   Updated: 2025/06/27 16:19:36 by matsuimiki    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* #include "minishell.h" */

int ft_pwd(char **args) ////the parameter here, we need to adjust later
{
    char *cwd;

    if (count_args(args) > 2)
        return (print_error("cd: too many arguments\n"), 1);
    cwd = getcwd(NULL, 0);
    if (!cwd)
        return (perror("pwd"), 1);
    ft_putstr(cwd);
    write (1, "\n", 1);
    free (cwd);
    return (0);
}
/* int main(int ac, char **av)
{
    (void)ac;
    if (av[1] && ft_strcmp(av[1], "pwd") == 0)
        ft_pwd(av);
    return(0);
} */