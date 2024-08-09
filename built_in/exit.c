/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:26:31 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/08 15:29:28 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_argument(char *arg)
{
	int	i;
	int	skip;
	int	sign;

	i = 0;
	skip = 0;
	while (arg[i] == ' ')
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		sign = 1 - 2 * (arg[i++] == '-');
	skip = i;
	if (arg[i] == '\0')
		return (false);
	while (arg[i])
		if (!ft_isdigit(arg[i++]))
			return (false);
	while (arg[skip] == '0')
		skip++;
	if ((ft_strncmp(arg + skip, "9223372036854775807", 19) > 0 && sign == 1)
		|| ft_strlen(arg + skip) > 19)
		return (false);
	if ((ft_strncmp(arg + skip, "9223372036854775808", 19) > 0 && sign == -1)
		|| ft_strlen(arg + skip) > 19)
		return (false);
	return (true);
}

void	ft_exit(t_shell *shell, t_cmd *cmd)
{
	int		len;
	char	**args;
	int		i;

	args = cmd->args;
	i = 1;
	len = 1;
	while (args[len])
		len++;
	if (len == 1)
		exit(shell->exit_status);
	if (check_argument(args[1]) == true && len > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		shell->exit_status = 1;
		return ;
	}
	else if (check_argument(args[1]) == false)
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit(255);
	}
	else if (check_argument(args[1]) == true && len >= 2)
		exit(ft_atoi(args[1]));
}
