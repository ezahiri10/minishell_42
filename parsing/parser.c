/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:05:00 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/18 23:48:01 by alafdili         ###   ########.fr       */
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

void	parser(t_shell *shell, t_token *tmp)
{
	int		i;
	int		flag;
	int		end_lst;

	i = -1;
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
		if (++i && flag != 1)
			tmp = tmp->next;
	}
	syntax_error_check(shell, tmp, flag);
}
