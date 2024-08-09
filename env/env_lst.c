/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:12:54 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/02 19:19:02 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(t_env *lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_env	*new_env(char *var, char *value)
{
	t_env	*new;

	new = malloc (sizeof(t_env));
	stock_addr(new, 1);
	if (!new)
		return (NULL);
	new->var = var;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!lst)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		temp = (*lst);
		while (temp -> next)
			temp = temp -> next;
		temp -> next = new;
	}
}

void	*add_env(char *var, char *value, t_env **head)
{
	t_env	*new;

	new = new_env(var, value);
	env_add_back(head, new);
	return (new);
}
