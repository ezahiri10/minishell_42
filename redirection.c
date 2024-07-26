/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:47:09 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/26 11:43:25 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

t_cmd	*creat_cmd(char *to_join, t_redir *redir)
{
	t_cmd	*cmd;
	char	**args;

	if (to_join == NULL)
		cmd = new_cmd(NULL, redir, NULL);
	else if ((*to_join == 127 && !to_join[1]) || !*to_join)
	{
		args = (char **)ft_malloc (sizeof(char *) * 2, 1);
		args[0] = ft_strdup("");
		args[1] = NULL;
		cmd = new_cmd (args[0], redir, args);
	}
	else
	{
		args = ft_split(to_join, 127);
		cmd = new_cmd(args[0], redir, args);
	}
	return (cmd);
}

void	join_word(char **to_join, t_token **start)
{
	while (*start && (*start)->join == JOINBLE)
	{
		if ((*start)->data.content != NULL)
			*to_join = ft_strjoin(*to_join, (*start)->data.content);
		*start = (*start)->next;
	}
	if ((*start)->data.content != NULL)
		*to_join = ft_strjoin(*to_join, (*start)->data.content);
	*start = (*start)->next;
}

void	check_herdoc(t_token *start, int *fd)
{
	if (start->type == HERE_DOC)
		*fd = start->data.fd;
	else
		*fd = -1;
}

void	redirection(t_shell *shell)
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

		// if (start->type != WORD)
		// {
		// 	check_herdoc(start, &fd);
		// 	join_word(&filename, &start->next);
		// 	add_redir(&redir, filename, start->type, fd);
		// 	start = start->next;
		// 	filename = NULL;
		// }
		// else if (start->type == WORD && start->join == JOINBLE)
		// 	join_word(&args, &start);
		// else if (start->type == WORD && start->join == NON_JOINBLE)
		// {
		// 	if (start->data.content != NULL)
		// 	{
		// 		args = ft_strjoin(args, char_to_string(127));
		// 		args = ft_strjoin(args, start->data.content);
		// 	}
		// 	start = start->next;
		// }