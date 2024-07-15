/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:12:10 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/15 20:37:24 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lstsize(t_token *lst)
{
	int		counter;
	t_token	*temp;

	temp = lst;
	counter = 0;
	while (temp != NULL)
	{
		counter++;
		temp = temp -> next;
	}
	return (counter);
}
