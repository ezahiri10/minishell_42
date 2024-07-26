/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:34:55 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/25 16:27:57 by ezahiri          ###   ########.fr       */
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
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

t_join	is_joinble(char c)
{
	if (c == ' ' || c == '\t' || c == '\0' || c == '|' || c == '>' || c == '<')
		return (NON_JOINBLE);
	return (JOINBLE);
}

// char *remove_quote(char *token)
// {
// 	char *new_token;
// 	char to_remove;
// 	int i;

// 	i = 0;
// 	new_token = ft_strdup(token);
// 	if (new_token[i] == '\"')
// 		to_remove = '\"';
// 	else if (new_token[i] == '\'')
// 		to_remove = '\'';
// 	else
// 		return (token);
// 	new_token++;
// 	while (new_token[i] != to_remove)
// 		i++;
// 	new_token[i] = '\0';
// 	return (new_token);
// }