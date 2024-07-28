/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:34:55 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/28 17:30:11 by alafdili         ###   ########.fr       */
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
	if (c == ' ' || c == '\t' || c == '\0' || c == '|' || c == '>' || c == '<')
		return (NON_JOINBLE);
	return (JOINBLE);
}

void	space_to_127(t_token *token)
{
	int	i;

	i = 0;
	if (token->state != IN_SINGALE && token->state != IN_DOUBLE)
	{
		while (token->data.content && token->data.content[i])
		{
			if (token->data.content[i] == ' ')
				token->data.content[i] = 127;
			i++;
		}
	}
}

// void	set_filename(char **filename, t_token **start, t_type *type)
// {
// 	*filename = ft_strjoin(*filename, char_to_string(127));
// 	while (*start && (*start)->join == JOINBLE)
// 	{
// 		if ((*start)->state != IN_SINGALE && (*start)->state != IN_DOUBLE
// 			&& ft_count((*start)->data.content, ' '))
// 		{
// 			*type = ERROR;
// 			break ;
// 		}
// 		if ((*start)->data.content == NULL)
// 			*filename = ft_strjoin(*filename, "");
// 		else
// 			*filename = ft_strjoin(*filename, (*start)->data.content);
// 		*start = (*start)->next;
// 	}
// 	if ((*start)->data.content != NULL)
// 	{
// 		if ((*start)->state != IN_SINGALE && (*start)->state != IN_DOUBLE
// 			&& ft_count((*start)->data.content, ' '))
// 			*type = ERROR;
// 		if (ft_strcmp((*start)->data.content))
// 		*filename = ft_strjoin(*filename, (*start)->data.content);
// 	}
// 	else
// 		*filename = ft_strjoin(*filename, "");
// 	if (!ft_strcmp(*filename, char_to_string(**filename)))
// 		*type = ERROR;
// 	*start = (*start)->next;
// }


// void	set_filename(char **filename, t_token **start, t_type *type)
// {
// 	*filename = ft_strjoin(*filename, char_to_string(127));
// 	if ((*start)->join == NON_JOINBLE)
// 	{
// 		if (!(*start)->data.content || ft_count((*start)->data.content, ' '))
// 			*type = ERROR;
// 		*filename = ft_strjoin(*filename, (*start)->data.content);
// 		*start = (*start)->next;
// 		return ;
// 	}
// 	while (*start && (*start)->join == JOINBLE)
// 	{
// 		if (check_space(*start, type))
// 			break ;
// 		if ((*start)->data.content != NULL)
// 			*filename = ft_strjoin(*filename, (*start)->data.content);
// 		*start = (*start)->next;
// 	}
// 	if ((*start)->data.content != NULL)
// 	{
// 		check_space(*start, type);
// 		*filename = ft_strjoin(*filename, (*start)->data.content);
// 	}
// 	else
// 		*type = ERROR;
// 	*start = (*start)->next;
// }