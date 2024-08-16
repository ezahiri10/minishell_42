/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:18:23 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/16 22:13:41 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_shell *shell, t_cmd *cmd)
{
	char	**args;
	int		i;
	int		error;

	i = 1;
	error = 0;
	args = cmd->args;
	if (!args[1])
		print_env(shell, shell->env_lst);
	while (args[i])
	{
		set_env(shell, args[i], &error);
		i++;
	}
	if (error != 0)
		shell->exit_status = 1;
	else
		shell->exit_status = 0;
}
