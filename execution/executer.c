/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:23:41 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/05 23:37:39 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_shell *shell, t_cmd *cmd, int *ends, t_cmd *last)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (redirection_check(shell->cmd, cmd->redir) == FAIL)
		exit(1);
	apply_redirections(cmd, ends, shell->input, last);
	if (!cmd->cmd)
	{
		close_fd(NULL, shell->cmd);
		exit (0);
	}
	if (cmd->cmd[0] == '\0')
		print_error(shell->cmd, (char *[2]){CNF, cmd->cmd}, 127);
	if ((cmd->cmd[0] == '/' || (cmd->cmd[0] == '.' && cmd->cmd[1] == '/'))
		&& check_executable(shell->cmd, cmd->cmd) == SUCCESS)
		cmd_path = cmd->cmd;
	else
	{
		cmd_path = check_cmd(ft_get_env_key(shell->env_lst, "PATH"), cmd->cmd);
		if (!cmd_path)
			print_error(shell->cmd, (char *[2]){CNF, cmd->cmd}, 127);
	}
	if (execve(cmd_path, cmd->args, shell->env) == -1)
		print_error(shell->cmd, (char *[2]){strerror(errno), "execve"}, errno);
}

int	exec_pipeline(t_shell *shell, t_cmd *cmd, t_cmd *next_cmd)
{
	pid_t	pid;
	int		ends[2];

	if (pipe(ends) == -1)
		return (perror("minishell: pipe"), FAIL);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (close(ends[0]), close(ends[1]), FAIL);
	}
	else if (pid == 0)
		exec_cmd(shell, cmd, ends, next_cmd);
	dup2(ends[0], 0);
	close(ends[0]);
	close (ends[1]);
	return (pid);
}

void	executer(t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	pid_t	last_cmd;

	if (shell->stoped)
		return ;
	shell->input[1] = dup(0);
	cmd = shell->cmd;
	tmp = cmd;
	while (cmd)
	{
		last_cmd = exec_pipeline(shell, cmd, cmd->next);
		if (last_cmd == FAIL)
			break ;
		cmd = cmd->next;
	}
	get_exit_status(shell, last_cmd);
	dup2(shell->input[1], 0);
	close(shell->input[1]);
	close_fd(NULL, shell->cmd);
}
