/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dilemeter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:32:25 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/07 13:32:47 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_delimiter(char *token, int *i, t_shell *shell, t_state state)
{
	char	c;
	int		start;
	t_join	join;
	char	*sub;

	*i += 1;
	start = *i;
	if (state == IN_SINGALE)
		c = '\'';
	else
		c = '\"';
	while (token[*i] != c && token[*i] != '\0')
		*i += 1;
	if (token[*i] == c)
		*i += 1;
	else if (!token[*i])
		return (display_syntax_error(shell), FAIL);
	join = is_joinble(token[*i]);
	sub = ft_substr(token, start, *i - start - 1);
	add_lst(sub, &shell->tokens, state, join);
	return (SUCCESS);
}

void	dollar_delimiter(char *token, int *i, t_token **head, t_state state)
{
	int		start;
	int		end;
	t_join	join;

	start = *i;
	end = *i + 1;
	while (token[end] && token[end] == '$')
		end++;
	if (token[end] == '?')
	{
		*i = end + 1;
		join = is_joinble(token[*i]);
		add_lst(ft_substr(token, start, *i - start), head, state, join);
		return ;
	}
	while (token[end] && (ft_isalnum(token[end]) || token[end] == '_'))
		end++;
	*i = end;
	join = is_joinble(token[end]);
	add_lst(ft_substr(token, start, *i - start), head, state, join);
}

void	word_delimiter(char *token, int *i, t_token **head, t_state state)
{
	int		start;
	t_join	join;

	start = *i;
	while (!is_special(token[*i]) && token[*i] != ' ' && token[*i])
	{
		if (token[*i] == '\t')
			break ;
		*i = *i + 1;
	}
	join = is_joinble(token[*i]);
	add_lst(ft_substr(token, start, *i - start), head, state, join);
}

void	opertor_delimiter(char *token, int *i, t_token **head, t_state state)
{
	if (token[*i] == '|')
		add_lst(ft_strdup("|"), head, state, NON_JOINBLE);
	else if (token[*i] == '<' && token[*i + 1] == '<')
	{
		add_lst(ft_strdup("<<"), head, state, NON_JOINBLE);
		*i += 1;
	}
	else if (token[*i] == '>' && token[*i + 1] == '>')
	{
		add_lst(ft_strdup(">>"), head, state, NON_JOINBLE);
		*i += 1;
	}
	else if (token[*i] == '<')
		add_lst(ft_strdup("<"), head, state, NON_JOINBLE);
	else if (token[*i] == '>')
		add_lst(ft_strdup(">"), head, state, NON_JOINBLE);
	*i += 1;
}
