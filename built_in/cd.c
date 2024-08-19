/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:01:47 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/19 19:27:22 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pwd(t_shell *shell, char *path)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		shell->cpy_pwd = join_env(shell->cpy_pwd, "/");
		path = dup_env(ft_strtrim(path, "/"));
		shell->cpy_pwd = join_env(shell->cpy_pwd, path);
	}
	else
	{
		shell->cpy_pwd = pwd;
		stock_addr(pwd, 1);
	}
}

void	chang_dir(t_shell *shell, char *path)
{
	shell->old_pwd = getcwd(NULL, 0);
	stock_addr(shell->old_pwd, 1);
	if (!shell->old_pwd)
		shell->old_pwd = shell->cpy_pwd;
	if (chdir(path) == -1)
	{
		shell->exit_status = 1;
		perror("Minishell: cd");
		return ;
	}
	check_pwd(shell, path);
	value_non_joinlble("OLDPWD", shell->old_pwd, shell, 1);
	value_non_joinlble("PWD", shell->cpy_pwd, shell, 1);
	shell->exit_status = 0;
}

void	ft_cd(t_shell *shell, t_cmd *cmd)
{
	char	*home;

	if (!cmd->args[1])
	{
		home = get_env_key(shell->env_lst, "HOME");
		if (!home)
		{
			shell->exit_status = 1;
			return (ft_putstr_fd("cd: HOME not set\n", 2));
		}
		chang_dir(shell, home);
	}
	else
		chang_dir(shell, cmd->args[1]);
}
