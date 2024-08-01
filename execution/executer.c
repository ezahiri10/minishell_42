/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:23:41 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/01 10:58:12 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_cmd(char *path, char *cmd)
{
	int		i;
	char	*cmd_path;
	char	**sub_path;

	cmd_path = NULL;
	i = 0;
	sub_path = ft_split(path, ':');
	while (sub_path[i])
	{
		sub_path[i] = ft_strjoin(sub_path[i], "/");
		cmd_path = ft_strjoin(sub_path[i], cmd);
		if (access(cmd_path, X_OK) != -1)
			return (cmd_path);
		cmd_path = NULL;
		i++;
	}
	return (NULL);
}

void ft_close(t_redir *head)
{
	t_redir	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->fd != -1 && tmp->fd != 0)
		{
			close (tmp->fd);
			tmp->fd = -1;
		}
		tmp = tmp->next;
	}
}

bool file_check(t_redir *file, char *erro_type)
{
	if (file->type == IN)
	{
		file->fd = open(file->filename, O_RDONLY);
		if (file->fd == -1)
			return (erro_type = strerror(errno), FAILURE);
	}
	else if (file->type == OUT)
	{
		file->fd = open(file->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (file->fd == -1)
			return (erro_type = strerror(errno), FAILURE);
	}
	else if (file->type == APPEND)
	{
		file->fd = open(file->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (file->fd == -1)
			return (erro_type = strerror(errno), FAILURE);
	}
	return (SUCCESS);
}

bool is_exist(t_redir *rdir, t_type type)
{
	t_redir *tmp;
	t_type	opposite;

	tmp = rdir;
	opposite = (type + 2) % 4;
	printf("type = %d opposite = %d\n", type, opposite);
	while (tmp)
	{
		if (tmp->type == type || tmp->type == opposite)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

bool redireciton_check(t_redir *lst)
{
	t_redir *tmp;
	char *err;

	tmp = lst;
	err = NULL;
	while (tmp)
	{
		if (file_check(tmp, err) == FAILURE)
		{
			ft_close(lst);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tmp->filename, 2);
			ft_putstr_fd(":", 2);
			ft_putendl_fd(err, 2);	
			return (FAILURE);
		}
		if (is_exist(tmp->next, tmp->type) == true)
		{
			close(tmp->fd);
			tmp->fd = -1;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

void    one_cmd_exec(t_shell *shell)
{
	// pid_t	pid;

	if (redireciton_check(shell->cmd->redir))
	{
		shell->exit_status = 1;
		return ;
	}
}

void    executer(t_shell *shell)
{
	int cmds_nb;

	cmds_nb = cmd_lstsize(shell->cmd);
	if (cmds_nb == 1)
		one_cmd_exec(shell);
	
}
