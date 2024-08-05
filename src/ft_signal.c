/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:54:49 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/05 23:45:40 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_handler(int s)
{
	int	status;

	if (wait(&status) == -1)
		g_recv_signal = s;
	g_recv_signal = status;
}

void	new_prompt(int s)
{
	int	status;

	if (wait(&status) == -1)
	{
		g_recv_signal = s;
		rl_replace_line("", 0);
		rl_on_new_line();
		close(0);
	}
	else
		g_recv_signal = status;
}

void	ft_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, quit_handler);
}
