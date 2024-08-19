/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:13:58 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/19 18:46:14 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
		printf ("%s\n", pwd);
	else if (shell->cpy_pwd)
		printf ("%s\n", shell->cpy_pwd);
	else
	{
		perror("Minishell: pwd");
		shell->exit_status = 1;
		free(pwd);
		return ;
	}
	shell->exit_status = 0;
	free(pwd);
}
