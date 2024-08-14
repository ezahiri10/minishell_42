/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:53:08 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/14 12:42:26 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_p_err(t_cmd *head, char **err_msg, int exit_code)
{
	close_fd(NULL, head);
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(err_msg[2], 2);
	ft_putstr_fd(err_msg[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_msg[0], 2);
	if (exit_code != -1)
		exit(exit_code);
}

char	*check_cmd(char *path, char *cmd)
{
	int		i;
	char	*cmd_path;
	char	**sub_path;

	i = 0;
	cmd_path = NULL;
	if (!path)
		return (NULL);
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

bool	check_executable(t_cmd *head, t_cmd *cmd)
{
	DIR	*dirp;
	int	len;

	len = ft_strlen(cmd->cmd) - 1;
	if (!(cmd->cmd[0] == '/' || (cmd->cmd[0] == '.' || cmd->cmd[1] == '/')
			|| cmd->cmd[len] == '/'))
		return (FAIL);
	if (access(cmd->cmd, X_OK) != -1)
	{
		dirp = opendir(cmd->cmd);
		if (dirp != NULL)
		{
			closedir(dirp);
			_p_err(head, (char *[3]){ISDIR, cmd->cmd, ""}, 126);
		}
	}
	else if (errno == ENOENT)
		_p_err(head, (char *[3]){strerror(errno), cmd->cmd, ""}, 127);
	else
		_p_err(head, (char *[3]){strerror(errno), cmd->cmd, ""}, 126);
	return (SUCCESS);
}
