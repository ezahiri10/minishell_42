/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:33:53 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/10 17:16:03 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_syntax_error(t_shell *shell)
{
	if (catch_signal(0, GET) == SIGINT)
	{
		shell->stoped = 1;
		return ;
	}
	ft_putstr_fd("Minishell: ", 2);
	ft_putendl_fd("syntax error", 2);
	shell->exit_status = 258;
	shell->stoped = 1;
}

void	close_rdir_fds(t_redir *head)
{
	t_redir	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->fd != -1 && tmp->fd != 0)
		{
			close (tmp->fd);
			tmp->fd = -1;
		}
		tmp = tmp->next;
	}
}

void	close_fd(t_token *token, t_cmd *head)
{
	while (token)
	{
		if (token->data.fd != -1 && token->data.fd != 0)
		{
			close (token->data.fd);
			token->data.fd = -1;
		}
		token = token->next;
	}
	while (head)
	{
		close_rdir_fds(head->redir);
		head = head->next;
	}
}

void	clean_up(t_shell *shell)
{
	ft_malloc(0, 0);
	stock_addr(NULL, 0);
	close(shell->input[0]);
	close_fd (shell->tokens, NULL);
	exit(1);
}

void	ft_export_error(char *arg, t_shell *shell)
{
	shell->exit_status = 1;
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}
