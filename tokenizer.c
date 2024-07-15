/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:12:57 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/15 19:52:54 by alafdili         ###   ########.fr       */
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

void	ft_tokenize(char *line, t_token **head)
{
	int	end;

	end = 0;
	while (line[end])
	{
		if (is_special(line[end]) == IN_SINGALE)
		{
			if (quote_delimiter(line, &end, head, IN_SINGALE))
				return ;
		}
		else if (is_special(line[end]) == IN_DOUBLE)
		{
			if (quote_delimiter(line, &end, head, IN_DOUBLE))
				return ;
		}
		else if (is_special(line[end]) == DOLLAR)
			dollar_delimiter(line, &end, head, DOLLAR);
		else if (is_special(line[end]) == 4)
			opertor_delimiter(line, &end, head, DEFAULT);
		else if (line[end] == ' ' || line[end] == '\t')
			end++;
		else
			word_delimiter(line, &end, head, DEFAULT);
	}
	free(line);
}
