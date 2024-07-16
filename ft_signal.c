/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:54:49 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/16 17:27:38 by ezahiri          ###   ########.fr       */
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

void	ft_signal()
{
	rl_catch_signals = 0;
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
}
