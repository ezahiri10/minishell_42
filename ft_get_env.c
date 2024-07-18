/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:34:30 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/18 12:39:09 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	equelchr(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*subenv(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	counter;

	if (!s)
		return (NULL);
	counter = 0;
	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (counter < len && s)
	{
		substr[counter] = s[start + counter];
		counter++;
	}
	substr[counter] = '\0';
	return (substr);
}

t_env	*ft_get_env(char **env)
{
	t_env	*lst;
	int		find;
	char	*value;
	int		i;

	i = 0;
	lst = NULL;
	while (env[i])
	{
		find = equelchr(env[i]);
		value = subenv(env[i] + find + 1, 0, ft_strlen (env[i]));
		if (!add_env(subenv(env[i], 0, find), value, &lst))
			return (NULL);
		i++;
	}
	return (lst);
}
