/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:34:48 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/02 21:18:08 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env_lst;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->var, tmp->value);
		tmp = tmp->next;
	}
}
