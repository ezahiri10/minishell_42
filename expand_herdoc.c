/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:21:53 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/24 17:21:38 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *is_not_expand(char *str, int *start)
{
    char *sub;
    int end;
 
    end = *start + 1;
    while (str[end] && str[end] != '\'')
        end++;
    if (str[end] == '\'')
        end++;
    sub = ft_substr(str, *start, end - *start);
    *start = end;
    // printf("is_not_expand = %s\n", sub);
    return (sub);
}

char    *is_expand(char *str, int *start, t_shell *shell)
{
    char *sub;
    int end;
 
    end = *start + 1;
    while (str[end] && str[end] != '\"')
        end++;
    if (str[end] == '\"')
        end++;
    sub = ft_substr(str, *start , end - *start);
    sub = search_dollar(shell, sub);
    *start = end;
    return (sub);
}

char	*here_doc_expand(t_shell *shell, char *line)
{
	int		i;
	char	*to_join;
	char	*expanded;

    i = 0;
	to_join = NULL;
	while (line[i])
	{
        if (line[i] == '\'')
            to_join = ft_strjoin(to_join, is_not_expand(line, &i));
        else if (line[i] == '\"')
            to_join = ft_strjoin(to_join, is_expand(line, &i, shell));
		else if (line[i] == '$')
		{
			expanded = dollar_expansion(limiter(&i, line), shell);
			to_join = ft_strjoin(to_join, expanded);
		}
		else
		{
			to_join = ft_strjoin(to_join, char_to_string(line[i]));
			i++;
		}
	}
    // printf("joined %s\n", to_join);
	return (to_join);
}

void heredoc_expansion(t_shell *shell, int *old_fd)
{
	int		write_fd;
	int		read_fd;
	char	*line;
	char	*expanded;
	
    expanded = NULL;
    write_fd = open("heredoc_expand", O_CREAT | O_WRONLY, 0666);
    read_fd = open("heredoc_expand", O_RDONLY);
    unlink("heredoc_expand");
	while (1)
	{
		line = get_next_line(*old_fd);
		if (!line)
			break ;
        expanded = here_doc_expand(shell, line);
        write(write_fd, expanded, ft_strlen(expanded));
	}
    close(write_fd);
    close (*old_fd);
    *old_fd = read_fd;
}
