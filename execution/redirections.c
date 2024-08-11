/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:05:36 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/11 13:23:26 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redirection_fds(t_redir *redir, t_type type)
{
	t_type	second_type;

	if (type == IN)
		second_type = HERE;
	else
		second_type = APPEND;
	while (redir)
	{
		if ((redir->type == type || redir->type == second_type)
			&& redir->fd != -1)
			return (redir->fd);
		redir = redir->next;
	}
	if (type == IN)
		return (0);
	return (1);
}

void	apply_redirections(t_cmd *head, int *ends, int *input, t_cmd *last)
{
	int	fds[2];

	fds[0] = get_redirection_fds(head->redir, IN);
	fds[1] = get_redirection_fds(head->redir, OUT);
	if (fds[0] != 0)
	{
		dup2(fds[0], 0);
		close(fds[0]);
	}
	if (fds[1] != 1)
	{
		dup2(fds[1], 1);
		close(fds[1]);
	}
	else if (fds[1] == 1 && last && ends)
		dup2(ends[1], 1);
	if (ends)
	{
		close(ends[1]);
		close(ends[0]);
		close(input[0]);
		close(input[1]);
	}
}
