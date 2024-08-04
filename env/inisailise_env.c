/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inisailise_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:34:30 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/03 10:31:19 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	inisailise_env(char **env, t_shell *shell)
{
	int		find;
	char	*value;
	char 	*name;
	int		i;

	i = 0;
	while (env[i])
	{
		find = researcher(env[i], '=');
		value = subenv(env[i] + find + 1, 0, ft_strlen (env[i]));
		name = subenv(env[i], 0, find);
		if (!name || !value)
			clean_up(shell);
		if (!add_env(name, value,  &shell->env_lst))
			clean_up(shell);
		i++;
	}
}
