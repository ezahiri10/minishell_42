/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:34:35 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/26 10:36:14 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(t_token **head, t_redir **redir, char **args)
{
	int		fd;
	char	*filename;

	filename = NULL;
	if ((*head)->type != WORD)
	{
		check_herdoc(*head, &fd);
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

t_cmd	*set_cmd(t_token *start, t_token *end)
{
	t_redir	*redir;
	char	*args;

	args = NULL;
	redir = NULL;
	while (start != end)
		check_cmd(&start, &redir, &args);
	return (creat_cmd(args, redir));
}
