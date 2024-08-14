/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:35:41 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/14 13:34:06 by alafdili         ###   ########.fr       */
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

int	open_here_fds(t_token *heredoc, int *write_fd)
{
	unlink("/tmp/.here_doc");
	*write_fd = open("/tmp/.here_doc", O_CREAT | O_RDWR, 0666);
	if (*write_fd == -1)
		return (perror("open heredoc"), FAIL);
	heredoc->data.fd = open("/tmp/.here_doc", O_RDONLY);
	if (heredoc->data.fd == -1)
		return (close(*write_fd), perror("open heredoc"), FAIL);
	unlink("/tmp/.here_doc");
	return (*write_fd);
}

void	heredoc_loop(t_shell *shell, char *limiter, int fd)
{
	char	*line;

	child_exist(2, SET);
	close_fd(shell->tokens, NULL);
	while (true)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, limiter))
		{
			if (shell->exit_status != 258)
				shell->exit_status = 0;
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	exit(0);
}

int	open_here_doc(t_shell *shell, t_token *heredoc, char *limiter)
{
	pid_t	pid;
	int		fd;

	fd = -1;
	if (shell->exit_status != 258 && open_here_fds(heredoc, &fd) == FAIL)
		return (FAIL);
	child_exist(1, SET);
	pid = fork();
	if (pid == -1)
	{
		close(fd);
		close (heredoc->data.fd);
		return (perror("Minishell: fork"), FAIL);
	}
	else if (pid == 0)
		heredoc_loop(shell, limiter, fd);
	waitpid(pid, &shell->exit_status, 0);
	shell->exit_status = WEXITSTATUS(shell->exit_status);
	if (shell->exit_status)
		catch_signal(SIGINT, SET);
	close(fd);
	child_exist(0, SET);
	return (SUCCESS);
}

bool	ft_here_doc(t_shell *shell, t_token *head)
{
	char	*limiter;

	while (head && catch_signal(0, GET) != SIGINT)
	{
		if (head->type == ERROR)
			return (FAIL);
		if (head->type == HERE && !ft_strcmp(head->data.content, "<<"))
		{
			limiter = join_limiter(head->next);
			if (open_here_doc(shell, head, limiter) == FAIL)
				return (close_fd (shell->tokens, NULL), FAIL);
			limiter = NULL;
		}
		head = head->next;
	}
	if (catch_signal(0, GET) == SIGINT)
		return (close_fd(shell->tokens, NULL), FAIL);
	return (SUCCESS);
}
