/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:50:28 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/12 14:10:24 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cwords(const char *s, char c)
{
	int	nwords;
	int	counter;

	nwords = 0;
	counter = 0;
	if (s == NULL || *s == '\0')
		return (0);
	while (*s)
	{
		counter = 0;
		while (*s == c)
			s++;
		if (*s)
		{
			while (s[counter] && s[counter] != c)
				counter++;
			nwords++;
		}
		s += counter;
	}
	return (nwords);
}

static void	*mfree(char **fstr, int c)
{
	int	counter;

	counter = 0;
	while (counter < c)
	{
		free(fstr[counter]);
		counter++;
	}
	free(fstr);
	return (NULL);
}

static char	**wlen(char **str, const char *s, char c)
{
	int	c1;
	int	c2;

	c1 = 0;
	c2 = 0;
	while (*s)
	{
		c1 = 0;
		while (*s == c && *s)
			s++;
		if (*s)
		{
			while (s[c1] != c && s[c1])
				c1++;
			str[c2] = (char *)ft_malloc(sizeof(char) * (c1 + 1), 1);
			if (str[c2] == NULL)
				return (mfree(str, c2));
			ft_strlcpy(str[c2], s, c1 + 1);
			c2++;
		}
		s += c1;
	}
	str[c2] = NULL;
	return (str);
}

char	**ft_split(const char *s, char c)
{
	char	**ns;
	int		nwords;

	if (!s)
		return (NULL);
	nwords = cwords(s, c);
	ns = (char **)ft_malloc(sizeof(char *) * (nwords + 1), 1);
	if (ns == NULL)
		return (NULL);
	return (wlen(ns, s, c));
}
