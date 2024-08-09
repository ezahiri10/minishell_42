/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:01:47 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/06 22:07:15 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_shell *shell, t_cmd *cmd)
{
	char	**args;
	char	*home;

	args = cmd->args;
	if (!args[1])
	{
		home = get_env_key(shell->env_lst, "HOME");
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
