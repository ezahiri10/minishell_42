/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:54:41 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/09 18:46:32 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exit_status(t_shell *shell, pid_t last_cmd)
{
	int	signal_nb;
	int	is_signaled;

	waitpid(last_cmd, &shell->exit_status, 0);
	signal_nb = WTERMSIG(g_recv_signal);
	is_signaled = WIFSIGNALED(g_recv_signal);
	if (is_signaled && signal_nb == SIGINT)
	{
		printf("\n");
		shell->exit_status = 130;
	}
	else if (is_signaled && signal_nb == SIGQUIT)
	{
		printf("Quit: 3\n");
		shell->exit_status = 131;
	}
	else
		shell->exit_status = WEXITSTATUS(shell->exit_status);
	while (wait(NULL) != -1)
		;
	if (signal_nb == SIGINT)
	{
		dup2(shell->input[0], 0);	
		g_recv_signal = 0;
	}
}
