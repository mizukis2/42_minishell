/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:34:28 by zekhatib          #+#    #+#             */
/*   Updated: 2025/08/04 04:52:56 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_len(const char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (0);
	if (!ft_isalpha((unsigned char)s[i]) && s[i] != '_')
		return (0);
	i++;
	while (s[i] && (ft_isalnum((unsigned char)s[i]) || s[i] == '_'))
		i++;
	return (i);
}

void	append_to_result(char **result, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(*result, str);
	free(*result);
	*result = tmp;
}

void	append_char_to_result(char **result, char c)
{
	char	s[2];

	s[0] = c;
	s[1] = '\0';
	append_to_result(result, s);
}

//Mizuki commented out this get_env_value, since this function is already in builtin_utils
/* char	*get_env_value(t_env *envp, char *key)//remove after adding env files
{
	t_env	*curr;

	curr = envp;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (ft_strdup(curr->value));
		curr = curr->next;
	}
	return (NULL);
} */
