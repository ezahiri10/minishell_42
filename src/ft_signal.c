/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:54:49 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/09 19:10:50 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	catch_signal(int s, bool set_or_get)
{
	static int signal;
	
	if (set_or_get == SET)
		signal = s;
	return (signal);	
}

bool	child_exist(bool true_or_false, bool mode)
{
	static bool exist;

	if (mode == SET)
		exist = true_or_false;
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
		rl_on_new_line();
		close(0);
	}
}

void	ft_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, quit_handler);
}
