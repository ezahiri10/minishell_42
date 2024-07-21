/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:05:00 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/21 16:43:57 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	def_type(t_token *token, t_type type)
{
	if (token)
	{
		if (token->type == type)
			return (true);
	}
	return (false);
}

char *__remove_new_line(char *line)
{
	int i;
	char *new_line;

	i = 0;
	new_line = ft_malloc(ft_strlen(line), 1);
	while (line[i] != '\n' && line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);	
}

int __error_position(t_token *head, t_token *node)
{
	int position;

	position = 0;
	while (head)
	{
		if (head->data == node->data && position == 0)
			return (-1);
		else if (head->data == node->data && head->next == NULL)
			return (1);
		else if (!ft_strcmp(head->data, "<<"))
			position++;
		head = head->next;
	}
	return (0);
}

bool open_here_doc(char *limiter)
{
	int fd;
	int fd2;
	char *line;
	line = NULL;

	fd = open(limiter, O_CREAT | O_TRUNC | O_RDWR, 0600);
	if (fd == -1)
		return (perror("open here_doc file"), false);
	fd2 = open(limiter, O_RDONLY);
	if (fd2 == -1)
		return (perror("open here_doc file"), false);
	unlink(limiter);
	while (g_recv_signal != 1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || !ft_strcmp(__remove_new_line(line), limiter))
			break ;
		write(fd, line, ft_strlen(line));
	}
	return (true);
}

void here_doc(t_token *head)
{

	while (head)
	{
		if (head->type == ERROR)
			return ;
		if (!ft_strcmp(head->data, "<<"))
		{
			
			if (open_here_doc(head->next->data) == false)	
				return;
		}
		head = head->next;
	}
}

void __syntax_error_def(t_shell *shell ,t_token *pst, int flag)
{
	int _error_location;

	if (flag != 0)
	{
		pst->type = ERROR;
		_error_location = __error_position(shell->tokens, pst);
		if (_error_location == -1 || !_error_location)
		{
			write(2, ""READ"Minishell: syntax error"END"\n", 36);
			shell->exit_status = 258;
			here_doc(shell->tokens);
		}
		else
		{
			here_doc(shell->tokens);
			write(2, ""READ"Minishell: syntax error"END"\n", 36);
			shell->exit_status = 258;
		}
	}
	else
		here_doc(shell->tokens);
}

void	ft_parser(t_shell *shell)
{
	int		i;
	int		flag;
	int		end_lst;
	t_token	*tmp;

	i = 0;
	flag = 0;
	tmp = shell->tokens;
	end_lst = lstsize(tmp);
	while (tmp)
	{
		if (def_type(tmp, PIPE) && i == 0)
			flag = 1;
		else if (def_type(tmp, PIPE) && def_type(tmp->next, PIPE))
			flag = 1;
		else if (!def_type(tmp, WORD) && i == end_lst - 1)
			flag = 1;
		else if (!def_type(tmp, PIPE) && !def_type(tmp, WORD)
			&& !def_type(tmp->next, WORD))
			flag = 1;
		if (flag == 1)
			break ;
		i++;
		tmp = tmp->next;
	}
	__syntax_error_def(shell, tmp, flag);
}
