/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:01:47 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/09 18:39:30 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_pwd(t_shell *shell, char *path)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		shell->old_pwd = join_env(shell->old_pwd, "/");
		path = dup_env(ft_strtrim(path, "/"));
		if (!ft_strcmp(path, ".."))
			shell->old_pwd = join_env(shell->old_pwd, "..");
		else if (!ft_strcmp(path, "."))
			shell->old_pwd = join_env(shell->old_pwd, ".");
		else
			shell->old_pwd = join_env(shell->old_pwd, path);
	}
	else
	{
		shell->old_pwd = pwd;
		stock_addr(pwd, 1);
	}
}
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
		perror("cd");
		return ;
	}
	check_pwd(shell, args[1]);
}
