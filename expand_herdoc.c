/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:21:53 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/26 10:37:24 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_expansion(t_shell *shell, int *old_fd)
{
	int		write_fd;
	int		read_fd;
	char	*line;
	char	*expanded;

	expanded = NULL;
	write_fd = open("heredoc_expand", O_CREAT | O_WRONLY, 0666);
	if (write_fd == -1)
		return (clean_up(shell));
	read_fd = open("heredoc_expand", O_RDONLY);
	if (read_fd == -1)
		return (close(write_fd), clean_up(shell));
	unlink("heredoc_expand");
	while (1)
	{
		line = get_next_line(*old_fd);
		if (!line)
			break ;
		expanded = search_dollar(shell, line);
		write(write_fd, expanded, ft_strlen(expanded));
	}
	close(write_fd);
	close (*old_fd);
	*old_fd = read_fd;
}
