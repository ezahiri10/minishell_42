/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:34:35 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/26 17:01:26 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fd(t_token *start, int *fd)
{
	if (start->type == HERE_DOC)
		*fd = start->data.fd;
	else
		*fd = -1;
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

t_cmd	*create_cmd(char *to_join, t_redir *redir)
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

void	get_cmd_part(t_token **head, t_redir **redir, char **args)
{
	int		fd;
	char	*filename;

	filename = NULL;
	if ((*head)->type != WORD)
	{
		set_fd(*head, &fd);
		join_word(&filename, &(*head)->next);
		add_redir(redir, filename, (*head)->type, fd);
		*head = (*head)->next;
		filename = NULL;
	}
	else if ((*head)->type == WORD && (*head)->join == JOINBLE)
		join_word(args, head);
	else if ((*head)->type == WORD && (*head)->join == NON_JOINBLE)
	{
		if ((*head)->data.content != NULL)
		{
			*args = ft_strjoin(*args, char_to_string(127));
			*args = ft_strjoin(*args, (*head)->data.content);
		}
		*head = (*head)->next;
	}
}

t_cmd	*get_simple_cmd(t_token *start, t_token *end)
{
	t_redir	*redir;
	char	*args;

	args = NULL;
	redir = NULL;
	while (start != end)
		get_cmd_part(&start, &redir, &args);
	return (create_cmd(args, redir));
}
