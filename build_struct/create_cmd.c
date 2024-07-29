/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:34:35 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/29 22:05:59 by alafdili         ###   ########.fr       */
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
	int		j;
	t_cmd	*cmd;
	char	**args;

	i = 0;
	args = ft_split(to_join, 127);
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == 4)
				args[i][j] = '\0';
			j++;
		}
		i++;
	}
	cmd = new_cmd(args[0], redir, args);
	return (cmd);
}

void	set_filename(char **filename, t_token **start, t_type *type)
{
	int	empty;

	empty = 0;
	while (*start && (*start)->join == JOINBLE)
	{
		empty += check_and_join(filename, *start, type);
		*start = (*start)->next;
	}
	if ((*start)->data.content != NULL)
		empty += check_and_join(filename, *start, type);
	else
		check_and_join(filename, *start, type);
	if (ft_count(*filename, 127) == (int)ft_strlen(*filename) && !empty)
		*type = ERROR;
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
