/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:12:57 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/11 17:13:00 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_spec(char c)
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

void	tokenizer(char *ln, t_shell *shell)
{
	int	i;

	i = 0;
	while (ln[i])
	{
		if (skiper(ln, i))
			i++;
		else if (is_spec(ln[i]) == IN_SINGALE || is_spec(ln[i]) == IN_DOUBLE)
		{
			if (quote_delimiter(ln, &i, shell, is_spec(ln[i])))
				break ;
		}
		else if (is_spec(ln[i]) == DOLLAR)
			dollar_delimiter(ln, &i, &shell->tokens, DOLLAR);
		else if (is_spec(ln[i]) == 4)
			opertor_delimiter(ln, &i, &shell->tokens, DEFAULT);
		else
			word_delimiter(ln, &i, &shell->tokens, DEFAULT);
	}
	if (!shell->tokens)
		shell->stoped = 1;
}
