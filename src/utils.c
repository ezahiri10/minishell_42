/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:34:55 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/03 10:04:37 by ezahiri          ###   ########.fr       */
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

int	check_and_join(char **filename, t_token *token, t_type *type)
{
	if (!token->data.content && type != NULL)
		*filename = ft_strjoin(*filename, char_to_string(127));
	else if (!token->data.content && type == NULL)
		*filename = ft_strjoin(*filename, token->data.content);
	else if (!*token->data.content)
	{
		if (type == NULL)
			*filename = ft_strjoin(*filename, char_to_string(4));
		else
			*filename = ft_strjoin(*filename, token->data.content);
		return (1);
	}
	else
	{
		if (token->state != IN_SINGALE && token->state != IN_DOUBLE
			&& ft_count(token->data.content, ' ') && type)
			*type = ERROR;
		*filename = ft_strjoin(*filename, token->data.content);
	}
	return (0);
}
