/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:47:09 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/19 19:28:51 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

t_cmd	*creat_cmd(t_cmd *cmd, char *to_join, t_redir *redir)
{
	char	**args;

	args = ft_split(to_join, ' ');
	cmd = new_cmd(args[0], redir, args);
	return (cmd);
}

t_cmd	*set_cmd(t_token *start, t_token *end)
{
	t_redir	*redir;
	t_token	*tmp;
	t_cmd	*cmd;
	char	*to_join;

	tmp = start;
	redir = NULL;
	to_join = NULL;
	cmd = malloc(sizeof(t_cmd));
	while (start != end)
	{
		if (start->type != WORD)
		{
			add_redir(&redir, start->next->data, start->type);
			start = start->next->next;
		}
		else
		{
			to_join = ft_strjoin(to_join, " ");
			to_join = ft_strjoin(to_join, start->data);
			start = start->next;
		}
	}
	cmd = creat_cmd(cmd, to_join, redir);
	return (cmd);
}

void	redirection(t_shell *shell)
{
	t_token	*end;
	t_token	*start;

	start = shell->tokens;
	end = shell->tokens;
	shell->cmd = NULL;
	while (end)
	{
		if (end->type == PIPE)
		{
			cmd_add_back(&shell->cmd, set_cmd(start, end));
			end = end->next;
			start = end;
		}
		else
			end = end->next;
	}
	if (end != start)
		cmd_add_back(&shell->cmd, set_cmd(start, end));
}
