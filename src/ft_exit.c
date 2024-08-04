/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:33:53 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/03 15:54:26 by ezahiri          ###   ########.fr       */
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
		if (token->data.fd != -1 && token->data.fd != 0)
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
	stock_addr(NULL, 0);
	close(shell->input);
	close_fd (shell);
	exit(1);
}

void	ft_export_error(char *arg, t_shell *shell)
{
	shell->exit_status = 1;
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}
