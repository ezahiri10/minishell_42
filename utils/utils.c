/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:34:55 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/13 10:43:55 by ezahiri          ###   ########.fr       */
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

t_join	is_joinble(char c)
{
	if (c == ' ' || c == '\t' || c == '\0'
		|| c == '|' || c == '>' || c == '<')
		return (NON_JOINBLE);
	return (JOINBLE);
}

char	*space_tab_trimer(char *str)
{
	char	*trimed;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while ((*str == '\t' || *str == ' ') && *str)
		str++;
	while (str[i] != '\t' && str[i] != ' ' && str[i])
		i++;
	trimed = ft_substr(str, 0, i);
	return (trimed);
}

void	space_to_127(t_token *token, t_state check_with)
{
	int	i;

	i = 0;
	if (token->state == DOLLAR && check_with == DOLLAR)
	{
		while (token->data.content && token->data.content[i])
		{
			if (token->data.content[i] == ' ' || token->data.content[i] == '\t')
				token->data.content[i] = 127;
			i++;
		}
	}
}

char	*remove_char(char *str)
{
	char	*new_str;
	int		char_nb;
	int		i;

	i = 0;
	if (!str)
		return (str);
	char_nb = ft_count(str, 4);
	if (char_nb == 0)
		return (str);
	new_str = ft_malloc(ft_strlen(str) - char_nb + 1, 1);
	while (*str)
	{
		if (*str != 4)
		{
			new_str[i] = *str;
			i++;
		}
		str++;
	}
	new_str[i] = '\0';
	return (new_str);
}
