/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dilemeter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:32:25 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/17 21:41:59 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_delimiter(char *token, int *i, t_shell *shell, t_state state)
{
	char	c;
	int		start;

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
	{
		write (2, "Enclosed quote!\n", 16);
		shell->exit_status = 258;
		free(token);
		ft_malloc (0, 0);
		shell->tokens = NULL;
		return (1);
	}
	add_lst(ft_substr(token, start, *i - start - 1), &shell->tokens, state);
	return (0);
}

void	dollar_delimiter(char *token, int *i, t_token **head, t_state state)
{
	int	start;
	int	end;

	start = *i;
	end = *i + 1;
	if (token[end] == '?')
		end++;
	while (token[end] && (ft_isalnum(token[end]) || token[end] == '_'))
		end++;
	*i = end;
	add_lst(ft_substr(token, start, *i - start), head, state);
}

void	word_delimiter(char *token, int *i, t_token **head, t_state state)
{
	int	start;

	start = *i;
	while (!is_special(token[*i]) && token[*i] != ' ' && token[*i])
	{
		if (token[*i] == '\t')
			break ;
		*i = *i + 1;
	}
	add_lst(ft_substr(token, start, *i - start), head, state);
}

void	opertor_delimiter(char *token, int *i, t_token **head, t_state state)
{
	if (token[*i] == '|')
		add_lst(ft_strdup("|"), head, state);
	else if (token[*i] == '<' && token[*i + 1] == '<')
	{
		add_lst(ft_strdup("<<"), head, state);
		*i += 1;
	}
	else if (token[*i] == '>' && token[*i + 1] == '>')
	{
		add_lst(ft_strdup(">>"), head, state);
		*i += 1;
	}
	else if (token[*i] == '<')
		add_lst(ft_strdup("<"), head, state);
	else if (token[*i] == '>')
		add_lst(ft_strdup(">"), head, state);
	*i += 1;
}
