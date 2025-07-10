//this is just for test of built in

#include "builtin.h"

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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
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

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10;
		result = result + str[i] - '0';
		i++;
	}
	return (result * sign);
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

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (destsize > 0)
	{
		i = 0;
		while (i < destsize - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (srclen);
}

static int	wordcount(char const *s, char c)
{
	int	words;
	int	inword;

	words = 0;
	inword = 0;
	while (*s)
	{
		if (*s != c && !inword)
		{
			words++;
			inword = 1;
		}
		else if (*s == c && inword)
		{
			inword = 0;
		}
		s++;
	}
	return (words);
}

static	char	*copyarr(char const *s, char c)
{
	char	*word;
	int		len;

	len = 0;
	while (s[len] && s[len] != c)
	{
		len++;
	}
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
	{
		return (NULL);
	}
	ft_strlcpy(word, s, len + 1);
	return (word);
}

static char	**freeall(char **result, int i)
{
	while (i > 0)
	{
		free (result[i - 1]);
		i--;
	}
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			result[i] = copyarr(s, c);
			if (!result[i])
				return (freeall(result, i));
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}


/* this used for mainly export function. */
char	*create_new_key(const char *arg)
{
	int		len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	return (ft_substr(arg, 0, len));
}

/* this used for mainly export function. */
char	*create_new_value(const char *arg)
{
	int	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	if (!arg[len])
		return (NULL);
	return (ft_strdup(arg + len + 1));
}

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
		new->exported = true;
	}
	else
	{
		if (set_key(new, str))
			return (NULL);
		new->value = NULL;
		new->exported = false;
	}
	new->next = NULL;
	return (new);
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

/* static function for update_env functon */
void	update_value(t_env *node, const char *new_value)        //changed
{
	if (!node)
		return;
	if (node->value)
		free(node->value);
	if (new_value)
		node->value = ft_strdup(new_value);
	else
		node->value = NULL;
}

/* static function for update_env functon */
static char	*create_env_str(const char *key, const char *path)
{
	char	*env_str;
	char	*temp;
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	if (path) //changed
		env_str = ft_strjoin(temp, path);
	else
		env_str = temp;
	free (temp);
	return (env_str);
}

void	update_env(const char *key, const char *path, t_env *envp)
{
	t_env *curr;
	char *env_line;
	t_env *new;

	curr = envp;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (path != NULL)
				curr->exported = true;
			return (update_value(curr, path));
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	if (path)
		env_line = create_env_str(key, path); //changed around here
	else
		env_line = ft_strdup(key);
	if (!env_line)
		return ;
	new = create_node(env_line);
	free (env_line);
	if (!new)
		return ;
	curr->next = new;
}

/* -------------------------------------------------------------- */