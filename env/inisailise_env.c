/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inisailise_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:34:30 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/14 11:06:57 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_env(char **env, t_shell *shell)
{
	int		find;
	char	*value;
	char	*name;
	int		i;

	i = 0;
	while (env[i])
	{
		find = researcher(env[i], '=');
		value = subenv(env[i] + find + 1, 0, ft_strlen (env[i]));
		name = subenv(env[i], 0, find);
		if (!name || !value)
			clean_up(shell);
		if (!add_env(name, value, &shell->env_lst))
			clean_up(shell);
		i++;
	}
}
