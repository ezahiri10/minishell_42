/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:52:56 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/07 19:13:38 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_export_word(char **to_join, t_token **start)
{
	int		i;
	t_token	*for_check;

	i = 0;
	for_check = *start;
	*to_join = ft_strjoin(*to_join, char_to_string(127));
	if ((*start)->next && (*start)->next->data.content
		&& !ft_strcmp((*start)->next->data.content, "="))
		for_check = *start;
	while (*start && (*start)->join == JOINBLE)
	{
		space_to_127(*start, for_check->state);
		check_and_join(to_join, *start, true);
		*start = (*start)->next;
	}
	if ((*start)->data.content != NULL)
	{
		space_to_127(*start, for_check->state);
		check_and_join(to_join, *start, true);
	}
	*start = (*start)->next;
}

void	join_word(char **to_join, t_token **start)
{
	*to_join = ft_strjoin(*to_join, char_to_string(127));
	while (*start && (*start)->join == JOINBLE)
	{
		space_to_127(*start, DOLLAR);
		check_and_join(to_join, *start, true);
		*start = (*start)->next;
	}
	if ((*start)->data.content != NULL)
	{
		space_to_127(*start, DOLLAR);
		check_and_join(to_join, *start, true);
	}
	*start = (*start)->next;
}
