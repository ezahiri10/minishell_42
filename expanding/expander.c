/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:13:21 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/31 20:35:59 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_shell *shell)
{
	char	*to_check;
	t_token	*tmp;

	if (shell->stoped)
		return ;
	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->state == DOLLAR)
		{
			tmp->data.origin = tmp->data.content;
			to_check = dollar_expansion(tmp->data.content, shell);
			if (!*to_check)
				tmp->data.content = NULL;
			else
				tmp->data.content = to_check;
		}
		else if (tmp->state == IN_DOUBLE)
			tmp->data.content = search_dollar(shell, tmp->data.content);
		else if (tmp->type == HERE && !check_is_double(tmp->next))
			heredoc_expansion(shell, &tmp->data.fd);
		tmp = tmp->next;
	}
}
