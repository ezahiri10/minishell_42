/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:34:35 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/27 23:56:07 by alafdili         ###   ########.fr       */
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

void	set_filename(char **filename, t_token **start)
{
	int i;

	*filename = ft_strjoin(*filename, char_to_string(127));
	while (*start && (*start)->join == JOINBLE)
	{
		i = 0;
		if ((*start)->state != IN_SINGALE && (*start)->state != IN_SINGALE)
		{
			while ((*start)->data.content[i])
			{
				if ((*start)->data.content[i] == ' ')
				{
					(*start)->type = ERROR;
					break ;
				}
				i++;
			}
		}
		if ((*start)->data.content != NULL)
			*filename = ft_strjoin(*filename, (*start)->data.content);
		*start = (*start)->next;
	}
	if ((*start)->data.content != NULL)
		*filename = ft_strjoin(*filename, (*start)->data.content);
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

	filename = NULL;
	if ((*head)->type != WORD)
	{
		set_fd(*head, &fd);
		set_filename(&filename, &(*head)->next);
		add_redir(redir, filename, (*head)->type, fd);
		*head = (*head)->next;
		filename = NULL;
	}
	else
		join_word(args, head);
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
