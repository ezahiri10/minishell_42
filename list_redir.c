/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lisrt_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:28:52 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/19 18:10:43 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redir(char *file, t_type type)
{
	t_redir	*new;

	new = ft_malloc(sizeof(t_redir), 1);
	new->file = file;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*temp;

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

void	add_redir(t_redir **lst, char *file, t_type type)
{
	t_redir	*new;

	new = new_redir(file, type);
	redir_add_back(lst, new);
}
