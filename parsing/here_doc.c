/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:35:41 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/03 14:32:08 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_limiter(t_token *nodes)
{
	char	*to_join;

	while (nodes->join == JOINBLE)
	{
		to_join = ft_strjoin(to_join, nodes->data.content);
		nodes = nodes->next;
	}
	to_join = ft_strjoin(to_join, nodes->data.content);
	return (to_join);
}

void	heredoc_loop(t_shell *shell, char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line && g_recv_signal == SIGINT)
		{
			shell->exit_status = 1;
			break ;
		}
		if (!line || !ft_strcmp(line, limiter))
		{
			if (shell->exit_status != 258)
				shell->exit_status = 0;
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
}

int	open_here_doc(t_shell *shell, t_token *heredoc, char *limiter)
{
	int		write_fd;

	write_fd = open("here_doc", O_CREAT | O_RDWR, 0666);
	if (write_fd == -1)
		return (perror("open heredoc"), FAILURE);
	heredoc->data.fd = open("here_doc", O_RDONLY);
	if (heredoc->data.fd == -1)
		return (close(write_fd), perror("open heredoc"), FAILURE);
	unlink("here_doc");
	heredoc_loop(shell, limiter, write_fd);
	close(write_fd);
	return (SUCCESS);
}

bool	here_doc(t_shell *shell, t_token *head, int input)
{
	char	*limiter;

	while (head && g_recv_signal != SIGINT)
	{
		if (head->type == ERROR)
			return (close(input), FAILURE);
		if (head->type == HERE_DOC && !ft_strcmp(head->data.content, "<<"))
		{
			limiter = join_limiter(head->next);
			if (shell->exit_status != 258)
			{
				if (open_here_doc(shell, head, limiter) == FAILURE)
					return (close(input), clean_up(shell), FAILURE);
			}
			else
				heredoc_loop(shell, limiter, -1);
			limiter = NULL;
		}
		head = head->next;
	}
	if (g_recv_signal == SIGINT)
		return (close_fd(shell), g_recv_signal = 0,
			dup2(input, 0), close(input), FAILURE);
	return (dup2(input, 0), close(input), SUCCESS);
}
