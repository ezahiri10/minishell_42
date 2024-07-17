/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:12:54 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/17 14:15:46 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *var, char *value)
{
	t_env	*new;

	new = malloc (sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = var;
	new->value = value;
	return (new);
}

void	add_env_front(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	new -> next = *lst;
	*lst = new;
}


void	clair_env(t_env **head)
{
	t_env	*tmp;
	t_env	*next;

	if (!head)
		return ;
	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->var);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}

void	*add_env(char *var, char *value, t_env **head)
{
	t_env	*new;

	new = new_env(var, value);
	if (!new)
	{
		clair_env(head);
		return (NULL);
	}
	add_env_front(head, new);
	return (new);
}
