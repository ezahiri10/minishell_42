/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:42:18 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/14 12:39:42 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(char *s, t_env **env)
{
	t_env	*prev;
	t_env	*tmp;

	prev = *env;
	tmp = *env;
	if (*env && !ft_strcmp(s, (*env)->var))
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

void	ft_unset(t_shell *shell, t_cmd *cmd)
{
	char	**args;
	int		i;

	args = cmd->args;
	args = cmd->args;
	i = 1;
	if (!args[i])
		return ;
	while (args[i])
	{
		if (is_valid(args[i]) == true)
			remove_env(args[i], &shell->env_lst);
		else
		{
			_p_err(NULL, (char *[3]){NAVI, args[i], "unset: "}, -1);
			shell->exit_status = 1;
			return ;
		}
		i++;
	}
}
