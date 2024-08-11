/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:47:09 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/11 16:35:51 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_simple_cmd(t_token *start, t_token *end)
{
	t_redir	*redir;
	char	*args;

	args = NULL;
	redir = NULL;
	while (start != end)
		get_cmd_part(&start, &redir, &args);
	get_cmd_part(NULL, NULL, NULL);
	return (create_cmd(args, redir));
}

void	get_pipeline(t_shell *shell)
{
	t_token	*end;
	t_token	*start;

	if (shell->stoped)
		return ;
	start = shell->tokens;
	end = shell->tokens;
	shell->cmd = NULL;
	while (end)
	{
		if (end->type == PIPE)
		{
			cmd_add_back(&shell->cmd, get_simple_cmd(start, end));
			end = end->next;
			start = end;
		}
		else
			end = end->next;
	}
	if (end != start)
		cmd_add_back(&shell->cmd, get_simple_cmd(start, end));
	cmd_type_def(shell);
	shell->tokens = NULL;
}
