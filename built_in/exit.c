/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:26:31 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/10 18:50:31 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_argument(char *arg)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (*arg == ' ')
		arg++;
	if (*arg == '-' || *arg == '+')
		sign = 1 - 2 * (*(arg++) == '-');
	if (*arg == '\0')
		return (false);
	while (arg[i])
		if (!ft_isdigit(arg[i++]))
			return (false);
	while (*arg == '0')
		arg++;
	if ((ft_strncmp(arg, "9223372036854775807", 19) > 0 && sign == 1)
		|| ft_strlen(arg) > 19)
		return (false);
	if ((ft_strncmp(arg, "9223372036854775808", 19) > 0 && sign == -1)
		|| ft_strlen(arg) > 19)
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
		print_error(NULL, (char *[3]){TMA, "exit", ""}, -1);
		shell->exit_status = 1;
		return ;
	}
	else if (check_argument(args[1]) == false)
	{
		print_error(NULL, (char *[3]){NAR, "exit", ""}, -1);
		exit(255);
	}
	else if (check_argument(args[1]) == true && len >= 2)
		exit(ft_atoi(args[1]));
}
