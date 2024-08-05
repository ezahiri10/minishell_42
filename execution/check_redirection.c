/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:31:46 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/05 23:37:02 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sum_redir_fds(t_redir *cmd_redir)
{
	int	sum_fd;

	sum_fd = 0;
	while (cmd_redir)
	{
		sum_fd += cmd_redir->fd;
		cmd_redir = cmd_redir->next;
	}
	return (sum_fd);
}

void	close_unused_fds(t_cmd *pipeline, t_redir *cur_cmd)
{
	t_redir	*tmp;
	int		cur_fds;

	cur_fds = sum_redir_fds(cur_cmd);
	while (pipeline)
	{
		tmp = pipeline->redir;
		if (sum_redir_fds(tmp) != cur_fds)
			close_rdir_fds(tmp);
		pipeline = pipeline->next;
	}
}

bool	is_exist(t_redir *rdir, t_type type)
{
	t_redir	*tmp;
	t_type	opposite;

	tmp = rdir;
	opposite = (type + 2) % 4;
	while (tmp)
	{
		if (tmp->type == type || tmp->type == opposite)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

bool	file_check(t_redir *file, char **erro_type)
{
	if (file->type == IN)
	{
		file->fd = open(file->file, O_RDONLY);
		if (file->fd == -1)
			return (*erro_type = strerror(errno), FAIL);
	}
	else if (file->type == OUT)
	{
		file->fd = open(file->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (file->fd == -1)
			return (*erro_type = strerror(errno), FAIL);
	}
	else if (file->type == APPEND)
	{
		file->fd = open(file->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (file->fd == -1)
			return (*erro_type = strerror(errno), FAIL);
	}
	return (SUCCESS);
}

bool	redirection_check(t_cmd *cmd, t_redir *lst)
{
	t_redir	*tmp;
	char	*err;

	tmp = lst;
	err = NULL;
	close_unused_fds(cmd, lst);
	while (tmp)
	{
		if (tmp->type == ERROR)
		{
			print_error(cmd, (char *[3]){AMBIGOUS, tmp->file}, -1);
			return (FAIL);
		}
		else if (file_check(tmp, &err) == FAIL)
			return (print_error(cmd, (char *[3]){err, tmp->file}, -1), FAIL);
		if (is_exist(tmp->next, tmp->type) == true)
		{
			close(tmp->fd);
			tmp->fd = -1;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
