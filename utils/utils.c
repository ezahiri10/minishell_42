/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:34:55 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/07 19:21:47 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*char_to_string(char c)
{
	char	*dest;

	dest = ft_malloc(sizeof(char) * 2, 1);
	dest[0] = c;
	dest[1] = '\0';
	return (dest);
}

int	ft_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

t_join	is_joinble(char c)
{
	if (c == ' ' || c == '\t' || c == '\0'
		|| c == '|' || c == '>' || c == '<')
		return (NON_JOINBLE);
	return (JOINBLE);
}

void	space_to_127(t_token *token, t_state check_with)
{
	int	i;

	i = 0;
	if (token->state == DOLLAR && check_with == DOLLAR)
	{
		while (token->data.content && token->data.content[i])
		{
			if (token->data.content[i] == ' ')
				token->data.content[i] = 127;
			i++;
		}
	}
}

void	check_and_join(char **filename, t_token *token, bool empty_str)
{
	if (!token->data.content)
		*filename = ft_strjoin(*filename, token->data.content);
	else if (!*token->data.content)
	{
		if (empty_str == true)
			*filename = ft_strjoin(*filename, char_to_string(4));
		else
			*filename = ft_strjoin(*filename, token->data.content);
	}
	else
		*filename = ft_strjoin(*filename, token->data.content);
}
