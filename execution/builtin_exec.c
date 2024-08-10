/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:29:31 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/10 15:54:12 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_builtin_cmd(t_shell *shell, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd, "env"))
		ft_env(shell);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		ft_cd(shell, cmd);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		ft_unset(shell, cmd);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd(shell);
	else if (!ft_strcmp(cmd->cmd, "export"))
		ft_export(shell, cmd);
	else if (!ft_strcmp(cmd->cmd, "echo"))
		ft_echo(shell, cmd);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		ft_exit(shell, cmd);
}

int	builtin_exec(t_shell *shell, t_cmd *cmd, int *ends)
{
	if (redirection_check(shell->cmd, cmd->redir) == FAIL)
		return (shell->exit_status =  1, FAIL);
	apply_redirections(cmd, ends, shell->input, cmd->next);
	get_builtin_cmd(shell, cmd);
	return (SUCCESS);
}
