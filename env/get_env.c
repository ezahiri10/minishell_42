/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:50:06 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/02 19:10:32 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	exist_env(char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, name) == 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

char    *_get_env(char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
