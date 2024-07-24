/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:47:09 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/24 19:39:54 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

t_cmd	*creat_cmd(t_cmd *cmd, char *to_join, t_redir *redir)
{
	char	**args;
	
	if (to_join == NULL)
		cmd = new_cmd(NULL, redir, NULL);
	else if ((*to_join == 127 && !to_join[1]) || !*to_join)
	{
		printf ("ddddddd\n");
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
	{
		printf ("%d\n", *(*start)->data.content);
		*to_join = ft_strjoin(*to_join, (*start)->data.content);
		printf ("to_join = %d\n", **to_join);
	}
	*start = (*start)->next;
}

void check_herdoc(t_token *start, int *fd)
{
	if (start->type == HERE_DOC)
		*fd = start->data.fd;
	else
		*fd = -1;
}
t_cmd	*set_cmd(t_token *start, t_token *end)
{
	t_redir	*redir;
	int		fd;
	t_cmd	*cmd;
	char	*filename;
	char    *args;
	t_type	type;

	fd = -1;
	args = NULL;
	redir = NULL;
	filename = NULL;
	cmd = malloc(sizeof(t_cmd));
	while (start != end)
	{
		if (start->type != WORD && start->next->join == JOINBLE)
		{
			check_herdoc(start, &fd);
			type = start->type;
			start = start->next;
			join_word(&filename, &start);
			add_redir(&redir, filename, type, fd);
			filename = NULL;
		}
		else if (start->type != WORD && start->next->join == NON_JOINBLE)
		{
			check_herdoc(start, &fd);
			type = start->type;
			start = start->next;
			add_redir(&redir, start->data.content, type, fd);
			start = start->next;
		}
		else if (start->type == WORD && start->join == JOINBLE)
		{
			join_word(&args, &start);
		}
		else if (start->type == WORD && start->join == NON_JOINBLE)
		{
			if (start->data.content != NULL)
			{
				printf ("-------------------\n");
			args = ft_strjoin(args, char_to_string(127));
			// printf ("argssss = %d\n", *args);
			args = ft_strjoin(args, start->data.content);
			// printf ("argssss = %d\n", *args);
			}
			start = start->next;
		}
	}
	// printf ("%s\n", )
	cmd = creat_cmd(cmd, args, redir);
	return (cmd);
}

void	redirection(t_shell *shell)
{
	t_token	*end;
	t_token	*start;

	if (!shell)
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
