//this is just for test of built in

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

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
	{
		return (1);
	}
	return (0);
}

void	ft_putstr(const char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}


char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (unsigned char)c)
		{
			return ((char *) str);
		}
		str++;
	}
	if (*str == (unsigned char)c)
	{
		return ((char *) str);
	}
	return (NULL);
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		if (s1[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *str1)
{
	char	*str2;
	size_t	len;
	size_t	i;

	len = ft_strlen(str1);
	i = 0;
	str2 = malloc((len + 1) * sizeof(char));
	if (str2 == NULL)
	{
		return (NULL);
	}
	while (str1[i])
	{
		str2[i] = str1[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!str)
		return (NULL);
	if (start > ft_strlen(str))
		return (ft_strdup(""));
	if (len > ft_strlen(str + start))
		len = ft_strlen(str + start);
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	length;
	char	*newstr;
	int		i;
	int		j;

	length = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	newstr = malloc((length + 1) * sizeof(char));
	if (!newstr)
	{
		return (NULL);
	}
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		newstr[j + i] = s2[j];
		j++;
	}
	newstr[j + i] = '\0';
	return (newstr);
}


int	set_key_value(t_env *node, char *str, int len)
{
	node->key = ft_substr(str, 0, len);
	if (!(node->key))
	{
		free_node(node);
		return (1);
	}
	node->value = ft_strdup(str + len + 1);
	if (!(node->value))
	{
		free_node(node);
		return (1);
	}
	return (0);
}

int	set_key(t_env *node, char *str)
{
	node->key = ft_strdup(str);
	if (!(node->key))
	{
		free_node(node);
		return (1);
	}
	return (0);
}

t_env *create_node(char *str)
{
	char	*eq;
	int		key_len;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	eq = ft_strchr(str, '=');
	if (eq)
	{
		key_len = eq - str;
		if (set_key_value(new, str, key_len))
			return (NULL);
	}
	else
	{
		if (set_key(new, str))
			return (NULL);
		new->value = NULL;
	}
	new->exported = true;
	new->next = NULL;
	return (new);
}

/* copy the environmental variable from main (char **envp) 
as linked list */
t_env	*copy_initial_env(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_node(envp[i]);
		if (!new_node)
		{
			free_node_list(head);
			return (NULL);
		}
		if (!head)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		i++;
	}
	return (head);
}

#include "minishell.h"

void	free_node(t_env *node)
{
	if (!node)
		return;
	if(node->key)
		free(node->key);
	if(node->value)
		free(node->value);
	free(node);
}

void	free_node_list(t_env *head)
{
	t_env *temp;
	while(head)
	{
		temp = head->next;
		free_node(head);
		head = temp;
	}
}

void	free_array (char **array)
{
	int	i;

	i = 0;
	while(array[i])
	{
		free(array[i]);
		i++;
	}
	free (array);
}

int	count_nodes(t_env *head)
{
	int	count;

	count = 0;
	while (head)
	{
		if (head->exported)
			count++;
		head = head->next;
	}
	return (count);
}

char	*complete_env_line(t_env *envp)
{
	char	*env_line;
	char	*temp;
	temp = ft_strjoin(envp->key, "=");
	if (!temp)
		return (NULL);
	env_line = ft_strjoin(temp, envp->value);
	if (!env_line)
	{
		free (temp);
		return (NULL);
	}
	free (temp);
	return (env_line);
}

/* this function convert the envp (linked list) to the envp (char **)
for the usage of execv. This array doesn't contain the unexported one
(export KEY : without = and value) */
char **list_to_array(t_env *envp)
{
	char	**array_envp;
	t_env *curr;
	int	i;
	int	count;

	count = count_nodes(envp);
	array_envp = malloc (sizeof(char *) * (count + 1));
	if (array_envp)
		return (NULL);
	curr = envp;
	i = 0;
	while (curr)
	{
		if (curr->exported)
		{
			array_envp[i] = complete_env_line(curr);
			if (!(array_envp[i]))
			{
				free_array(array_envp);
				return (NULL);
			}
			i++;
		}
		curr = curr->next;
	}
	array_envp[i] = NULL;
	return (array_envp);
}

/* static function for update_env functon */
static void	update_value(t_env *node, const char *new_value)
{
	if (!node)
		return;
	if (node->value)
		free(node->value);
	node->value = ft_strdup(new_value);
}

/* static function for update_env functon */
static char	*create_env_str(const char *key, const char *path)
{
	char	*env_str;
	char	*temp;
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	env_str = ft_strjoin(temp, path);
	free (temp);
	return (env_str);
}

/* update the environmental variable (linked list) by 
updating the path or adding the new node */
void	update_env(const char *key, const char *path, t_env *envp)
{
	t_env *curr;
	char *env_line;
	t_env *new;

	curr = envp;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (update_value(curr, path));
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	env_line = create_env_str(key, path);
	if (!env_line)
		return ;
	new = create_node(env_line);
	free (env_line);
	if (!new)
		return ;
	curr->next = new;
}