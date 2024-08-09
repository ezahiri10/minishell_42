/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_print_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:15:16 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/08 13:46:17 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(t_env *lst)
{
	t_env	*tmp;
	int		i;
	int		j;
	int		size;

	size = env_size(lst);
	i = 0;
	while (i < size)
	{
		j = 0;
		tmp = lst;
		while (j < size - i - 1)
		{
			if (ft_strcmp(tmp->var, tmp->next->var) > 0)
			{
				ft_swap(&tmp->var, &tmp->next->var);
				ft_swap(&tmp->value, &tmp->next->value);
			}
			j++;
			tmp = tmp->next;
		}
		i++;
	}
}

void	print_env(t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		sort_env(env);
		while (env)
		{
			if (env->value)
				printf("declare -x %s=\"%s\"\n", env->var, env->value);
			else
				printf("declare -x %s\n", env->var);
			env = env->next;
		}
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}
