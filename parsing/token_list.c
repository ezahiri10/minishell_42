/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:38:06 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/07 19:05:02 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_type(char *str)
{
	if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	if (!ft_strncmp(str, ">>", 2))
		return (APPEND);
	if (!ft_strncmp(str, "<<", 2))
		return (HERE);
	if (!ft_strncmp(str, "<", 1))
		return (IN);
	if (!ft_strncmp(str, ">", 1))
		return (OUT);
	else
		return (WORD);
}

t_token	*ft_new_token(char *content, t_state s, t_join join)
{
	t_token	*new_node;

	new_node = ft_malloc(sizeof(t_token), 1);
	if (!new_node)
		return (NULL);
	new_node->data.content = content;
	new_node->state = s;
	new_node->join = join;
	new_node->data.fd = -1;
	new_node->data.origin = content;
	if (s == DEFAULT)
		new_node->type = check_type(content);
	else
		new_node->type = WORD;
	new_node -> next = NULL;
	return (new_node);
}

void	ft_add_token(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!lst)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		temp = (*lst);
		while (temp -> next)
			temp = temp -> next;
		temp -> next = new;
	}
}

void	add_lst(char *content, t_token **lst, t_state state, t_join join)
{
	t_token	*new;

	new = ft_new_token(content, state, join);
	ft_add_token(lst, new);
}
