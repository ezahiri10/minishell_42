/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:05:00 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/15 12:13:45 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool idenetify_type(t_type type)
{
    if (type != PIPE && type != WORD)
        return (true);
    return (false);
}


void ft_parser(t_token **tokens)
{
    int i;
    int end_lst;
    t_token *tmp;

    i = 0;
    tmp = *tokens;
    end_lst = lstsize(tmp);
    while (tmp)
    {
        if (tmp->type == PIPE && i == 0)
        {
            write(2, "\033[33mminishell: syntax error\033[0m\n", 34);
            *tokens = NULL;
            return ;
        }
        else if (tmp->type == PIPE && tmp->next  && tmp->next->type == PIPE)
        {
            write(2, "\033[33mminishell: syntax error\033[0m\n", 34);
            *tokens = NULL;
            return ;
        }
        else if (tmp->type != WORD && i == end_lst - 1)
        {
            write(2, "\033[33mminishell: syntax error\033[0m\n", 34);
            *tokens = NULL;
            return ;
        }
        else if (idenetify_type(tmp->type) && idenetify_type(tmp->next->type))
        {
            write(2, "\033[33mminishell: syntax error\033[0m\n", 34);
            *tokens = NULL;
            return ;
        }
        i++;
        tmp = tmp->next;
    }
}
