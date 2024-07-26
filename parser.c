/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:05:00 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/26 14:03:42 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokens_size(t_token *lst)
{
	int		counter;
	t_token	*temp;

	temp = lst;
	counter = 0;
	while (temp != NULL)
	{
		counter++;
		temp = temp -> next;
	}
	return (counter);
}

static bool	check_type(t_token *token, t_type type)
{
	if (token)
	{
		if (token->type == type)
			return (true);
	}
	return (false);
}

int	get_error_position(t_token *head, t_token *err_node)
{
	int	pos;

	pos = 0;
	while (head)
	{
		if (head->data.content == err_node->data.content && pos == 0)
			return (-1);
		else if (head->next && head->next->data.content == err_node->data.content && pos == 0) // this line fixed the bug : << < ll "openinig herdoc"
			return (-1);
		else if (head->data.content == err_node->data.content && head->next == NULL)
			return (1);
		else if (!ft_strcmp(head->data.content, "<<"))
			pos++;
		{
			head->type = ERROR;
			return (-1);
		}
		else if (head->data.content == err_node->data.content && head->next == NULL)
			return (1);
		else if (!ft_strcmp(head->data.content, "<<"))
			pos++;
		head = head->next;
	}
	return (0);
}

void	syntax_error_check(t_shell *shell, t_token *limiter, int flag)
{
	int	error_location;

	if (flag != 0)
	{
		limiter->type = ERROR;
		error_location = get_error_position(shell->tokens, limiter);
		if (error_location == -1 || !error_location)
		{
			display_error(shell);
			here_doc(shell, shell->tokens);
		}
		else
		{
			shell->exit_status = 258;
			here_doc(shell, shell->tokens);
			display_error(shell);
		}
	}
	else if (here_doc(shell, shell->tokens) == FAILURE)
		shell->stoped = 1;
}

void	parser(t_shell *shell, t_token *tmp)
{
	int		i;
	int		flag;
	int		end_lst;

	i = 0;
	flag = 0;
	tmp = shell->tokens;
	end_lst = tokens_size(tmp);
	if (shell->stoped)
		return ;
	while (tmp && flag != 1)
	{
		if (check_type(tmp, PIPE) && i == 0)
			flag = 1;
		else if (check_type(tmp, PIPE) && check_type(tmp->next, PIPE))
			flag = 1;
		else if (!check_type(tmp, WORD) && i == end_lst - 1)
			flag = 1;
		else if (!check_type(tmp, PIPE) && !check_type(tmp, WORD)
			&& !check_type(tmp->next, WORD))
			flag = 1;
		if (++i && flag == 0)
			tmp = tmp->next;
	}
	syntax_error_check(shell, tmp, flag);
}
