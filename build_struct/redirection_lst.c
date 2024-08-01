/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:28:52 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/31 16:04:05 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redir(char *file, t_type type, int fd)
{
	t_redir	*new;

	new = ft_malloc(sizeof(t_redir), 1);
	new->fd = fd;
	new->filename = file;
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

void	add_redir(t_redir **lst, char *file, t_type type, int fd)
{
	t_redir	*new;

	new = new_redir(file, type, fd);
	redir_add_back(lst, new);
}
