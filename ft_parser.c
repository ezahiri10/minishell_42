/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:05:00 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/17 10:32:12 by alafdili         ###   ########.fr       */
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

void	display_syntax_error(t_shell *shell, int *flag)
{
	write(2, ""READ"minishell: syntax error"END"\n", 36);
	shell->exit_status = 258;
	*flag = 1;
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
			display_syntax_error(shell, &flag);
		else if (def_type(tmp, PIPE) && def_type(tmp->next, PIPE))
			display_syntax_error(shell, &flag);
		else if (!def_type(tmp, WORD) && i == end_lst - 1)
			display_syntax_error(shell, &flag);
		else if (!def_type(tmp, PIPE) && !def_type(tmp, WORD)
			&& !def_type(tmp->next, WORD))
			display_syntax_error(shell, &flag);
		if (flag == 1)
			return ;
		i++;
		tmp = tmp->next;
	}
}
