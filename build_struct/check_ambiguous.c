/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambiguous.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:53:39 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/10 13:14:42 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(const char *s)
{
	int	nwords;
	int	counter;

	nwords = 0;
	counter = 0;
	if (s == NULL || *s == '\0')
		return (1);
	while (*s)
	{
		counter = 0;
		while (*s == ' ' || *s == '\t')
			s++;
		if (*s)
		{
			while (s[counter] && s[counter] != ' ' && s[counter] != '\t')
				counter++;
			nwords++;
		}
		s += counter;
	}
	return (nwords);
}

bool	check_ambiguous(t_token *token)
{
	char	*to_join;

	to_join = NULL;
	while (token && token->join == JOINBLE)
	{
		if (token->state == DOLLAR)
			to_join = ft_strjoin(to_join, token->data.content);
		else if (!*token->data.content)
			to_join = ft_strjoin(to_join, token->data.content);
		else
			to_join = ft_strjoin(to_join, "X");
		token = token->next;
	}
	if (token->state == DOLLAR)
		to_join = ft_strjoin(to_join, token->data.content);
	else if (!*token->data.content)
		to_join = ft_strjoin(to_join, token->data.content);
	else
		to_join = ft_strjoin(to_join, "X");
	if (!to_join || count_words(to_join) != 1)
		return (false);
	return (true);
}
