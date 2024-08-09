/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:12:57 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/03 08:54:07 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special(char c)
{
	if (c == '\'')
		return (IN_SINGALE);
	else if (c == '\"')
		return (IN_DOUBLE);
	else if (c == '$')
		return (DOLLAR);
	else if (c == '|' || c == '<' || c == '>')
		return (4);
	return (0);
}

bool	skiper(char *line, int i)
{
	if ((line[i] == '$' && (line[i + 1] == '\'' || line[i + 1] == '\"')))
		return (true);
	if (line[i] == ' ' || line[i] == '\t')
		return (true);
	return (false);
}

void	tokenizer(char *line, t_shell *shell)
{
	int	end;

	end = 0;
	while (line[end])
	{
		if (skiper(line, end))
			end++;
		else if (is_special(line[end]) == IN_SINGALE)
		{
			if (quote_delimiter(line, &end, shell, IN_SINGALE))
				break ;
		}
		else if (is_special(line[end]) == IN_DOUBLE)
		{
			if (quote_delimiter(line, &end, shell, IN_DOUBLE))
				break ;
		}
		else if (is_special(line[end]) == DOLLAR)
			dollar_delimiter(line, &end, &shell->tokens, DOLLAR);
		else if (is_special(line[end]) == 4)
			opertor_delimiter(line, &end, &shell->tokens, DEFAULT);
		else
			word_delimiter(line, &end, &shell->tokens, DEFAULT);
	}
}
