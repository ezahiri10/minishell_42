/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambiguous.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:53:39 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/07 21:49:06 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!to_join || count_words(to_join, ' ') > 1)
		return (false);
	return (true);
}
