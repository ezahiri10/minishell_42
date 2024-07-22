/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:05:00 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/22 17:46:52 by alafdili         ###   ########.fr       */
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

int __error_position(t_token *head, t_token *node)
{
	int position;

	position = 0;
	while (head)
	{
		if (head->data.content == node->data.content && position == 0)
			return (-1);
		else if (head->data.content == node->data.content && head->next == NULL)
			return (1);
		else if (!ft_strcmp(head->data.content, "<<"))
			position++;
		head = head->next;
	}
	return (0);
}

void __syntax_error_check(t_shell *shell ,t_token *pst, int flag)
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
			here_doc(shell);
		}
		else
		{
			here_doc(shell);
			write(2, ""READ"Minishell: syntax error"END"\n", 36);
			shell->exit_status = 258;
			shell = NULL;
		}
	}
	else if (here_doc(shell) == FAILURE)
		shell = NULL;
}

void	ft_parser(t_shell *shell)
{
	int		i;
	int		flag;
	int		end_lst;
	t_token	*tmp;

	if (!shell)
		return ;
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
	__syntax_error_check(shell, tmp, flag);
}
