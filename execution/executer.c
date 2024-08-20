/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:23:41 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/20 01:15:18 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_shell *sh, t_cmd *cmd, int *ends, t_cmd *last)
{
	char	*cmd_path;
	char	*path;

	path = get_env_key(sh->env_lst, "PATH");
	cmd_path = NULL;
	if (redirection_check(sh->cmd, cmd->redir) == FAIL)
		exit(1);
	apply_redirs(sh, cmd->redir, ends, last);
	if (!cmd->cmd)
	{
		close_fd(NULL, sh->cmd);
		exit (0);
	}
	if (path && *path && (cmd->cmd[0] == '\0' || !ft_strcmp(cmd->cmd, "..")))
		_p_err(sh->cmd, (char *[3]){CNF, cmd->cmd, ""}, 127);
	if (check_executable(sh->cmd, cmd->cmd) == SUCCESS)
		cmd_path = cmd->cmd;
	else
	{
		cmd_path = check_cmd(sh, path, cmd->cmd);
		if (!cmd_path)
			_p_err(sh->cmd, (char *[3]){CNF, cmd->cmd, ""}, 127);
	}
	if (execve(cmd_path, cmd->args, sh->env) == -1)
		_p_err(sh->cmd, (char *[3]){strerror(errno), "execve", ""}, errno);
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
	{
		if (cmd->type == true)
		{
			builtin_exec(shell, cmd, ends);
			exit (shell->exit_status);
		}
		else
			exec_cmd(shell, cmd, ends, next_cmd);
	}
	if (dup2(ends[0], 0) == -1)
		return (close_and_perror(shell, (int [2]){ends[0], ends[1]}, -1), FAIL);
	return (close(ends[0]), close(ends[1]), pid);
}

void	exec_one_cmd(t_shell *shell)
{
	pid_t	pid;
	int		save[2];

	if (shell->cmd->type == true)
	{
		save[0] = dup(0);
		save[1] = dup(1);
		if (save[0] == -1 || save[1] == -1)
			return (close_and_perror(shell, (int [2]){save[0], save[1]}, -1));
		builtin_exec(shell, shell->cmd, NULL);
		if (dup2(save[0], 0) == -1 || dup2(save[1], 1) == -1)
			return (close_and_perror(shell, (int [2]){save[0], save[1]}, -1));
		return (close_and_perror(NULL, (int [2]){save[0], save[1]}, -1));
	}
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"));
	else if (pid == 0)
		exec_cmd(shell, shell->cmd, NULL, shell->cmd->next);
	get_exit_status(shell, pid);
	close_fd(NULL, shell->cmd);
}

void	pipeline_loop(t_shell *shell)
{
	t_cmd	*cmd;
	pid_t	last_id;

	cmd = shell->cmd;
	shell->input = dup(0);
	if (shell->input == -1)
		return (close_and_perror(shell, NULL, -1));
	child_exist(1, SET);
	while (cmd)
	{
		last_id = exec_pipeline(shell, cmd, cmd->next);
		if (last_id == FAIL)
		{
			kill(0, SIGINT);
			break ;
		}
		cmd = cmd->next;
	}
	get_exit_status(shell, last_id);
	if (dup2(shell->input, 0) == -1)
		return (close_and_perror(shell, (int [2]){shell->input, -1}, -1));
	close(shell->input);
	shell->input = -1;
	close_fd(NULL, shell->cmd);
}

void	executer(t_shell *shell)
{
	if (shell->stoped)
		return ;
	if (shell->cmd && !shell->cmd->next)
	{
		exec_one_cmd(shell);
		return ;
	}
	pipeline_loop(shell);
}
