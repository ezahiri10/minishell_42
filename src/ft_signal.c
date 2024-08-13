/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:54:49 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/13 10:11:10 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	catch_signal(int s, bool set_or_get)
{
	static int	signal;

	if (set_or_get == SET)
		signal = s;
	return (signal);
}

bool	child_exist(bool is_exist, bool mode)
{
	static bool	exist;

	if (mode == SET)
		exist = is_exist;
	return (exist);
}

void	quit_handler(int s)
{
	if (child_exist(0, GET) == false)
		catch_signal(s, SET);
}

void	new_prompt(int s)
{
	if (child_exist(0, GET) == false)
	{
		catch_signal(s, SET);
		rl_replace_line("", 0);
		close(0);
	}
}

void	ft_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, quit_handler);
}
