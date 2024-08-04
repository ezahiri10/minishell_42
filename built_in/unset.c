/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:42:18 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/02 19:04:35 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(char *s, t_env **env)
{
	t_env	*prev;
	t_env	*tmp;

	prev = *env;
	tmp = *env;
	if (!ft_strcmp(s, (*env)->var))
	{
		*env = (*env)->next;
		return ;
	}
	while (tmp)
	{
		prev = tmp;
		if (tmp->next && ft_strcmp(s, tmp->next->var) == 0)
		{
			prev->next = tmp->next->next;
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_unset(t_shell *shell)
{
	char	**args;
	int		i;

	args = shell->cmd->args;
	i = 1;
	if (!args[i])
		return ;
	while (args[i])
	{
		remove_env(args[i], &shell->env_lst);
		i++;
	}
}
