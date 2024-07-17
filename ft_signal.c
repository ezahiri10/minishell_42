/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:54:49 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/17 19:48:28 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_prompt(int s)
{
	if (s == SIGINT)
		printf ("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
}
