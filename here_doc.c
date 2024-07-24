/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:35:41 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/24 16:07:20 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *remove_quote(char *token)
{
	char *new_token;
	char to_remove;
	int i;

	i = 0;
	new_token = ft_strdup(token);
	if (new_token[i] == '\"')
		to_remove = '\"';
	else if (new_token[i] == '\'')
		to_remove = '\'';
	else
		return (token);
	new_token++;
	while (new_token[i] != to_remove)
		i++;
	new_token[i] = '\0';
	return (new_token);
}

char *_add_new_line(char *line)
{
	int i;
	char *new_line;

	i = 0;
	new_line = ft_malloc(ft_strlen(line), 1);
	while (line[i] != '\n' &&  line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);	
}

int open_here_doc(t_shell *shell, t_token *heredoc, char *limiter)
{
	int fd;
	char *line;
	line = NULL;

	(void)shell;
	fd = open("here_doc", O_CREAT | O_RDWR, 0600);
	if (fd == -1)
		return (perror("open here_doc file"), FAILURE);
	heredoc->data.fd = open("here_doc", O_RDONLY);
	if (heredoc->data.fd == -1)
		return (perror("open here_doc file"), FAILURE);
	unlink("here_doc");
	while (1)
	{
		line = readline("> ");
		if (!line && g_recv_signal == SIGINT)
		{
			close(fd);
			shell->exit_status = 1;
			g_recv_signal = 0;
			return (SUCCESS);
		}
		if (!line || !ft_strcmp(line, limiter))
		{
			close(fd);
			shell->exit_status = 0;
			return (SUCCESS);
		}
		line = ft_strjoin(line, "\n");
		write(fd, line, ft_strlen(line));
	}
	return (SUCCESS);
}

bool here_doc(t_shell *shell)
{
	int input;
	char *join_limeter;
	t_token *tmp;
	t_token *head;

	head = shell->tokens;
	join_limeter = NULL;
	input = dup(0);
	while (head)
	{
		if (head->type == ERROR)
			return (FAILURE);
		if (head->type == HERE_DOC && !ft_strcmp(head->data.content, "<<"))
		{
			tmp = head->next;
			while (tmp->join == JOINBLE)
			{
				join_limeter = ft_strjoin(join_limeter, tmp->data.content);
				tmp = tmp->next;
			}
			join_limeter = ft_strjoin(join_limeter, tmp->data.content);
			if (open_here_doc(shell, head, join_limeter) == FAILURE)
				return (FAILURE);
			join_limeter = NULL;
		}
		head = head->next;
	}
	dup2(input, 0);
	close(input);
    return (SUCCESS);
}
