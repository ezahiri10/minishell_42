/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:20:24 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/03 14:43:41 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_recv_signal = 0;

void	__ctrl_d(t_shell *shell)
{
	close(shell->input);
	close_fd(shell);
	stock_addr(NULL, 0);
	ft_malloc(0, 0);
	printf("\x1b[FMinishell$ exit\n");
	exit(shell->exit_status);
}

void	check_builtin(t_shell *shell)
{
	if(!shell->cmd)
		return ;
	if (shell->cmd->type == 1 && ft_strcmp(shell->cmd->path, "env") == 0)
		ft_env(shell);
	else if (shell->cmd->type == 1 && ft_strcmp(shell->cmd->path, "cd") == 0)
		ft_cd(shell);
	else if (shell->cmd->type == 1 && ft_strcmp(shell->cmd->path, "unset") == 0)
		ft_unset(shell);
	else if (shell->cmd->type == 1 && ft_strcmp(shell->cmd->path, "pwd") == 0)
		ft_pwd(shell);
	else if (shell->cmd->type == 1 && ft_strcmp(shell->cmd->path, "export") == 0)
		ft_export(shell);
	else if (shell->cmd->type == 1 && ft_strcmp(shell->cmd->path, "echo") == 0)
		ft_echo(shell->cmd);
	else if (shell->cmd->type == 1 && ft_strcmp(shell->cmd->path, "exit") == 0)
		ft_exit(shell);
}
void	interpreter(t_shell *shell, char *line)
{
	if (g_recv_signal == SIGINT)
	{
		shell->exit_status = 1;
		g_recv_signal = 0;
	}
	add_history(line);
	tokenizer(line, shell);
	parser(shell, shell->tokens);
	expander(shell);
	get_pipeline(shell);
	check_builtin(shell);
	close_fd(shell);
}

void	mini_shell(t_shell *shell)
{
	char	*line;

	shell->input = dup(0);
	while (1)
	{
		shell->stoped = 0;
		line = readline("Minishell$ ");
		stock_addr(line, 2);
		if (!line && g_recv_signal == SIGINT)
		{
			dup2(shell->input, 0);
			shell->exit_status = 1;
			g_recv_signal = 0;
			continue ;
		}
		if (!line)
			__ctrl_d(shell);
		interpreter(shell, line);
		ft_malloc(0, 0);
		shell->tokens = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	ft_signal();
	ft_memset(&shell, 0, sizeof(t_shell));
	shell.input = -1;
	shell.env = env;
	inisailise_env(env, &shell);
	mini_shell(&shell);
}
