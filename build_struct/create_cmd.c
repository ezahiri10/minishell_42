/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:34:35 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/31 00:23:46 by alafdili         ###   ########.fr       */
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
	int		i;
	t_cmd	*cmd;
	char	**args;

	i = 0;
	if (to_join == NULL)
		return (new_cmd(NULL, redir, NULL));
	args = ft_split(to_join, 127);
	while (args && args[i])
	{
		args[i] = ft_strtrim(args[i], char_to_string(4));
		i++;
	}
	cmd = new_cmd(args[0], redir, args);
	return (cmd);
}

void	set_filename(char **filename, t_token **start, t_type *type)
{
	int		empty;
	char	*save;

	empty = 0;
	save = NULL;
	while (*start && (*start)->join == JOINBLE)
	{
		empty += check_and_join(filename, *start, type);
		save = ft_strjoin(save, (*start)->data.origin);
		*start = (*start)->next;
	}
	empty += check_and_join(filename, *start, type);
	save = ft_strjoin(save, (*start)->data.origin);
	if ((ft_count(*filename, 127) == (int)ft_strlen(*filename)
			&& !empty) || *type == ERROR)
	{
		*type = ERROR;
		*filename = save;
	}
	*start = (*start)->next;
}

void	get_cmd_part(t_token **head, t_redir **redir, char **args)
{
	static int	i;
	int			fd;
	t_type		rd_type;
	char		*filename;

	if (!args)
	{
		i = 0;
		return ;
	}
	filename = NULL;
	if (!ft_strcmp((*head)->data.content, "export"))
		i++;
	if ((*head)->type != WORD)
	{
		set_fd(*head, &fd);
		rd_type = (*head)->type;
		set_filename(&filename, &(*head)->next, &rd_type);
		add_redir(redir, filename, rd_type, fd);
		*head = (*head)->next;
	}
	else if (i == 1)
		join_export_word(args, head);
	else
		join_word(args, head);
}
