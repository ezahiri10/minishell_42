/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:01:47 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/02 20:27:31 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_shell *shell)
{
	char	**args;
	char	*home;

	args = shell->cmd->args;
	if (!args[1])
	{
		home = _get_env("HOME", shell->env_lst);
		if (!home)
		{
			shell->exit_status = 1;
			return (ft_putstr_fd("cd: HOME not set\n", 2));
		}
		if (chdir(home) == -1)
			perror("cd");
	}
	else if (chdir(args[1]) == -1)
	{
		shell->exit_status = 1;
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("\n", 2);
	}
}
