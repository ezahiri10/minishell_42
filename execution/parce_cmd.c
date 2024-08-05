/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:53:08 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/05 23:46:55 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_cmd *head, char **err_msg, int exit_code)
{
	close_fd(NULL, head);
	ft_putstr_fd("Minishell: ", 2);
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

bool	*check_executable(t_cmd *head, char *path)
{
	int	fd;

	fd = open(path, O_RDWR);
	if (fd == -1)
	{
		if (errno != 2)
			print_error(head, (char *[2]){strerror(errno), path}, 126);
		else
			print_error(head, (char *[2]){strerror(errno), path}, 127);
	}
	close(fd);
	return (SUCCESS);
}
