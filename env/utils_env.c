/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:29:13 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/07 19:40:18 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	researcher(char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}

char	*dup_env(char *s)
{
	char	*dup;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	dup = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	stock_addr(dup, 1);
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*join_env(char *s1, char *s2)
{
	char	*constr;
	int		flen;
	int		slen;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	flen = ft_strlen(s1);
	slen = ft_strlen(s2);
	constr = (char *) malloc((flen + slen + 1) * sizeof(char));
	stock_addr(constr, 1);
	if (constr == NULL)
		return (NULL);
	ft_strlcpy (constr, s1, flen + 1);
	ft_strlcat (constr, s2, (flen + slen + 1));
	return (constr);
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
	stock_addr(substr, 1);
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
