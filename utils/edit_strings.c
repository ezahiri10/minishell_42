/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:45:28 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/14 10:47:58 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*remove_char(char *str, char c)
{
	char	*new_str;
	int		char_nb;
	int		i;

	i = 0;
	if (!str)
		return (str);
	char_nb = ft_count(str, c);
	if (char_nb == 0)
		return (str);
	new_str = ft_malloc(ft_strlen(str) - char_nb + 1, 1);
	while (*str)
	{
		if (*str != c)
		{
			new_str[i] = *str;
			i++;
		}
		str++;
	}
	new_str[i] = '\0';
	return (new_str);
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
