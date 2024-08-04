/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:18:23 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/03 12:39:53 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_shell *shell)
{
	char	**args;
	int		i;

	i = 1;
	args = shell->cmd->args;
	if (!args[1])
	{
		print_env(shell->env_lst);
		return ;
	}
	while (args[i])
	{
		set_env(shell, args[i]);
		i++;
	}
	return ;
}
