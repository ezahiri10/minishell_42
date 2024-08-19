/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:05:36 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/19 16:22:18 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redirection_fds(t_redir *redir, t_type type)
{
	t_type	second_type;

	second_type = (type + 2) % 4;
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

void	apply_redirs(t_shell *shell, t_redir *head, int *ends, t_cmd *last)
{
	int	fds[2];
	int	rvalue[2];

	fds[0] = get_redirection_fds(head, IN);
	fds[1] = get_redirection_fds(head, OUT);
	if (fds[0] != 0)
	{
		rvalue[0] = dup2(fds[0], 0);
		close(fds[0]);
	}
	if (fds[1] != 1)
	{
		rvalue [1] = dup2(fds[1], 1);
		close(fds[1]);
	}
	else if (fds[1] == 1 && last && ends)
		rvalue[1] = dup2(ends[1], 1);
	if (ends)
		close_and_perror(NULL, (int [2]){ends[0], ends[1]}, -1);
	close_and_perror(NULL, (int [2]){shell->input, -1}, -1);
	if (rvalue[0] == -1 || rvalue[1] == -1)
		close_and_perror(shell, NULL, 1);
}
