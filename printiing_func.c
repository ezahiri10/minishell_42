/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printiing_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:49:21 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/05 19:50:12 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_sruct(t_shell *shell)
{
	t_cmd	*tmp;
	int		i;

	if (shell->stoped)
		return ;
	tmp = shell->cmd;
	while (tmp)
	{
		i = 0;
		if (tmp->type == true)
			printf(""YEL"cmd is builtin"END"\n");
		else
			printf(""READ"cmd not builtin"END"\n");
		printf("cmd: %s\n", tmp->cmd);
		if (!tmp->args)
			printf("args: NULL\n");
		write(1, "args: ", 6);
		while (tmp->args && tmp->args[i])
		{
			write(1, tmp->args[i], ft_strlen(tmp->args[i]));
			write(1, " ", 1);
			i++;
		}
		printf("\n");
		while (tmp->redir)
		{
			printf("redir: %s\tfd==%d\ttype[%d\n", tmp->redir->file,
				tmp->redir->fd, tmp->redir->type);
			if (tmp->redir->type == ERROR)
				printf("----- type [ambigous\n");
			else
				printf("----- type [%d\n", tmp->redir->type);
			tmp->redir = tmp->redir->next;
		}
		tmp = tmp->next;
	}
}

void	print_line(t_shell *shell)
{
	t_token	*head;

	head = shell->tokens;
	while (head)
	{
		if ( head->join == JOINBLE)
			printf("data [%s]is JOINABLE\n", head->data.content);
		else
			printf("data [%s]is NOT JOINABLE\n", head->data.content);
		head = head->next;
	}
}

void	print_here_doc(t_shell *shell)
{
	t_token	*token;
	char	*line;
	int		i;

	if (!shell)
		return ;
	i = 0;
	token = shell->tokens;
	while (token)
	{
		if (!ft_strcmp(token->data.content, "<<"))
		{
			printf(""YEL"here_doc [%d]"END"\n", i + 1);
			while (1)
			{
				line = get_next_line(token->data.fd);
				if (!line)
					break ;
				printf("--- %s\n", line);
			}
			i++;
		}
		token = token->next;
	}
}
