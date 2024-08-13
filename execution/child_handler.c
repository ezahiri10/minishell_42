/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:54:41 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/12 17:12:07 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exit_status(t_shell *shell, pid_t last_cmd)
{
	int	signal_nb;
	int	is_signaled;

	child_exist(1, SET);
	waitpid(last_cmd, &shell->exit_status, 0);
	is_signaled = WIFSIGNALED(shell->exit_status);
	signal_nb = WTERMSIG(shell->exit_status);
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
	child_exist(0, SET);
}
