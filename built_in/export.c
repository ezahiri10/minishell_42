/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:18:23 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/12 17:08:32 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_shell *shell, t_cmd *cmd)
{
	char	**args;
	int		i;

	i = 1;
	args = cmd->args;
	if (!args[1])
	{
		print_env(shell, shell->env_lst);
		return ;
	}
	while (args[i])
	{
		set_env(shell, args[i]);
		i++;
	}
	return ;
}
