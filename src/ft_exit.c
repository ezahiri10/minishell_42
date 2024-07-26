/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:33:53 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/26 11:07:51 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error(t_shell *shell)
{
	write(2, ""READ"Minishell: syntax error"END"\n", 36);
	shell->exit_status = 258;
	shell->stoped = 1;
}

void	close_fd(t_shell *shell)
{
	t_token	*token;

	token = shell->tokens;
	while (token)
	{
		if (token->data.fd != -1)
		{
			close (token->data.fd);
			token->data.fd = -1;
		}
		token = token->next;
	}
}

void	clean_up(t_shell *shell)
{
	ft_malloc(0, 0);
	clair_env(&shell->env_lst);
	close(shell->input);
	close_fd (shell);
	exit(1);
}
