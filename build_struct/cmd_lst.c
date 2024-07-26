/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:36:35 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/26 20:50:19 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(char *cmd, t_redir *redir, char **args)
{
	t_cmd	*new;

	new = ft_malloc(sizeof(t_cmd), 1);
	new->path = cmd;
	new->redir = redir;
	new->args = args;
	new->next = NULL;
	return (new);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	if (!lst)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		temp = (*lst);
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}
