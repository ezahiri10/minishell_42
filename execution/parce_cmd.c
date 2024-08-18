/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:53:08 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/18 15:03:22 by alafdili         ###   ########.fr       */
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

void	cmd_sub_check(t_cmd *head, char *cmd)
{
	DIR	*dirp;

	if (access(cmd, X_OK) != -1)
	{
		dirp = opendir(cmd);
		if (dirp != NULL)
		{
			closedir(dirp);
			_p_err(head, (char *[3]){ISDIR, cmd, ""}, 126);
		}
	}
	else if (errno == ENOENT)
		_p_err(head, (char *[3]){strerror(errno), cmd, ""}, 127);
	else
		_p_err(head, (char *[3]){strerror(errno), cmd, ""}, 126);
}

char	*check_cmd(t_shell *shell, char *path, char *cmd)
{
	int		i;
	char	*cmd_path;
	char	**sub_path;

	i = 0;
	cmd_path = NULL;
	if (!path || !*path)
	{
		cmd_sub_check(shell->cmd, cmd);
		return (cmd);
	}
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
	if (ft_strchr(cmd, '/'))
		cmd_sub_check(shell->cmd, cmd);
	return (NULL);
}

bool	check_executable(t_cmd *head, char *cmd)
{
	int	len;

	len = ft_strlen(cmd) - 1;
	if (!(cmd[0] == '\0' || cmd[0] == '/' || (cmd[0] == '.' || cmd[1] == '/')
			|| cmd[len] == '/'))
		return (FAIL);
	cmd_sub_check(head, cmd);
	return (SUCCESS);
}
