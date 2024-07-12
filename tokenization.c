/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:15:25 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/12 09:38:30 by ezahiri          ###   ########.fr       */
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

void ft_tokenize(char *line, t_token **head)
{
	int	end;

	end = 0;
	while (*line && *line == 32)
		line++;
	while (line[end])
	{
		if (is_special(line[end]) == IN_SINGALE)
			quote_delemiter(line, &end, head, IN_SINGALE);
		else if (is_special(line[end]) == IN_DOUBLE)
			quote_delemiter(line, &end, head, IN_DOUBLE);
		else if (is_special(line[end]) == DOLLAR)
			dollar_delemiter(line, &end, head, DOLLAR);
		else if (is_special(line[end]) == 4)
			opertor_delemiter(line ,&end, head, DEFAULT);
		else if (line[end] == ' ')
			end++;
		else
			word_delemiter(line, &end, head, DEFAULT);
	}
}
