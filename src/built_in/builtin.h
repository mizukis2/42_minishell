//delete when this is marged to the main code

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <string.h>
# include <termcap.h>
# include <stdbool.h>

/* envp */
typedef struct s_env {
    char    *key;
    char    *value;
    bool    exported;
    struct s_env *next;
} t_env;

//main
int	execute_builtin(char **args, t_env *envp);
int main(int ac, char **av, char **envp);

//from dummy
void	update_env(const char *key, const char *path, t_env *envp);
char	*complete_env_line(t_env *envp);
int	count_nodes(t_env *head);
void	free_array (char **array);
t_env	*copy_initial_env(char **envp);
void	free_node_list(t_env *head);
t_env *create_node(char *str);
int	set_key(t_env *node, char *str);
int	set_key_value(t_env *node, char *str, int len);
void	free_node(t_env *node);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *str, unsigned int start, size_t len);
char	*ft_strdup(const char *str1);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *str, int c);
void	ft_putstr(const char *str);
int	ft_isalnum(int c);
int	ft_isalpha(int c);
int	ft_isdigit(int c);
int	ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
void	update_value(t_env *node, const char *new_value) ;
char	*create_new_key(const char *arg);
char	**ft_split(char const *s, char c);

//utils
int	count_args(char **args);
char	*get_env_value(t_env *envp, char *key);
void	print_error(const char *msg);
char	*create_new_value(const char *arg);

//function - built-in, this should be impliment right parameters later
int		execute_builtin(char **args, t_env *envp);
int		ft_echo(char **args);
int		ft_pwd(char **args);
int		ft_env(char **args, t_env *envp);
int		ft_export(char **args, t_env *envp);
int		ft_cd(char **args, t_env *envp);
int		ft_unset(char **args, t_env **envp);
int		ft_exit(char **args);

#endif
