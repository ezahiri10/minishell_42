/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:34:35 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/29 00:56:39 by alafdili         ###   ########.fr       */
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

void	set_filename(char **filename, t_token **start, t_type *type)
{
	int	empty;

	empty = 0;
	while (*start && (*start)->join == JOINBLE)
	{
		empty += check_and_add(filename, *start, type);
		*start = (*start)->next;
	}
	if ((*start)->data.content != NULL)
		empty += check_and_add(filename, *start, type);
	else
		check_and_add(filename, *start, type);
	if (ft_count(*filename, 127) == (int)ft_strlen(*filename) && !empty)
		*type = ERROR;
	*start = (*start)->next;
}

void	join_word(char **to_join, t_token **start)
{
	int	i;

	i = 0;
	*to_join = ft_strjoin(*to_join, char_to_string(127));
	while (*start && (*start)->join == JOINBLE)
	{
		space_to_127(*start);
		if ((*start)->data.content != NULL)
			*to_join = ft_strjoin(*to_join, (*start)->data.content);
		*start = (*start)->next;
	}
	if ((*start)->data.content != NULL)
	{
		space_to_127(*start);
		*to_join = ft_strjoin(*to_join, (*start)->data.content);
	}
	*start = (*start)->next;
}

void	get_cmd_part(t_token **head, t_redir **redir, char **args)
{
	int		fd;
	char	*filename;
	t_type	rd_type;

	filename = NULL;
	if ((*head)->type != WORD)
	{
		set_fd(*head, &fd);
		rd_type = (*head)->type;
		set_filename(&filename, &(*head)->next, &rd_type);
		add_redir(redir, filename, rd_type, fd);
		*head = (*head)->next;
		filename = NULL;
	}
	else
		join_word(args, head);
}
