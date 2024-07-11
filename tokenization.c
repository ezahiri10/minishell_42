/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:15:25 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/11 21:56:52 by ezahiri          ###   ########.fr       */
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

void quote_delemiter(char *token, int *i, t_token **head, t_state state)
{
	char c;
	int start;

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
		return ;
	}
	add_lst(ft_substr(token, start, *i - start - 1), head, state);
}

void dollar_delemiter(char *token, int *i, t_token **head, t_state state)
{
	int	start;
	int	end; 
	
	start = *i;
	end = *i + 1;
	while (token[end] && (ft_isalnum(token[end]) || token[end] == '_')) 
		end++;
	*i = end;
	add_lst(ft_substr(token + start, 0, end), head, state);
}

void word_delemiter(char *token, int *i, t_token **head, t_state state)
{
	int start;

	start = *i;
	while (!is_special(token[*i]) && token[*i] != ' ' && token[*i])
		*i = *i + 1;
	add_lst(ft_substr(token, start, *i - start), head, state);
}

void opertor_delemiter(char *token, int *i, t_token **head, t_state state)
{
	if (token[*i] == '|')
		add_lst(ft_strdup("|") , head, state);
	else if (token[*i] == '<' && token[*i + 1] == '<')
	{
		add_lst(ft_strdup("<<") , head, state);
		*i += 1;
	}
	else if (token[*i] == '>' && token[*i + 1] == '>')
	{
		add_lst(ft_strdup(">>") , head, state);
		*i += 1;
	}
	else if (token[*i] == '<')
		add_lst(ft_strdup("<") , head, state);
	else if (token[*i] == '>')
		add_lst(ft_strdup(">") , head, state);
	*i += 1;
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
			dollar_delemiter(&line[end], &end, head, DOLLAR);
		else if (is_special(line[end]) == 4)
			opertor_delemiter(line ,&end, head, DEFAULT);
		else if (line[end] == ' ')
			end++;
		else
			word_delemiter(line, &end, head, DEFAULT);
	}
}
