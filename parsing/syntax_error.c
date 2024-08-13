/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:02:07 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/13 19:11:56 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_error_position(t_token *head, t_token *err_node)
{
	int		pos;
	char	*content;

	pos = 0;
	content = err_node->data.content;
	while (head)
	{
		if (head->data.content == content && pos == 0)
			return (-1);
		else if (head->data.content == content && head->next == NULL)
			return (1);
		else if (!ft_strcmp(head->data.content, "<<"))
			pos++;
		head = head->next;
	}
	return (0);
}

void	syntax_error_check(t_shell *shell, t_token *limiter, int flag)
{
	int	error_location;

	if (flag != 0)
	{
		limiter->type = ERROR;
		error_location = get_error_position(shell->tokens, limiter);
		if (error_location == -1 || !error_location)
		{
			display_syntax_error(shell);
			ft_here_doc(shell, shell->tokens);
		}
		else
		{
			shell->exit_status = 258;
			ft_here_doc(shell, shell->tokens);
			display_syntax_error(shell);
		}
	}
	else if (ft_here_doc(shell, shell->tokens) == FAIL)
		shell->stoped = 1;
	catch_signal(0, SET);
}
