/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:36:35 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/06 15:22:22 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_lst_size(t_cmd *lst)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_cmd	*new_cmd(char *cmd, t_redir *redir, char **args)
{
	t_cmd	*new;

	new = ft_malloc(sizeof(t_cmd), 1);
	new->cmd = cmd;
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
