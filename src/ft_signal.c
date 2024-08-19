/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:54:49 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/18 20:55:37 by alafdili         ###   ########.fr       */
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

int	child_exist(int is_exist, bool mode)
{
	static int	exist;

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
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (child_exist(0, GET) == 2)
	{
		printf("\n");
		exit (1);
	}
}

void	ft_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, quit_handler);
}
