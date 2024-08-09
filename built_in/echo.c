/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:42:34 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/09 19:03:42 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_n(char *str)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		i += 2;
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] != '\0')
			return (false);
		else
			return (true);
	}
	return (false);
}

void	ft_echo(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (cmd->args[i] && check_n(cmd->args[i]))
	{
		n = 1;
		i++;
	}
	while (cmd->args[i] && cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n == 0)
		ft_putstr_fd("\n", 1);
	shell->exit_status = 0;
}
