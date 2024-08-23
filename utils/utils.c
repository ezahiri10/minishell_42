/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:34:55 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/23 19:09:31 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lst_to_arr(t_env *env)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = ft_malloc((env_size(env) + 1) * sizeof(char *), 1);
	while (env)
	{
		new_env[i] = ft_strjoin(env->var, "=");
		new_env[i] = ft_strjoin(new_env[i], env->value);
		env = env -> next;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	*char_to_string(char c)
{
	char	*dest;

	dest = ft_malloc(sizeof(char) * 2, 1);
	dest[0] = c;
	dest[1] = '\0';
	return (dest);
}

t_join	is_joinble(char c)
{
	if (c == ' ' || c == '\t' || c == '\0'
		|| c == '|' || c == '>' || c == '<')
		return (NON_JOINBLE);
	return (JOINBLE);
}

int	ft_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	close_and_perror(t_shell *shell, int *to_close, int exit)
{
	if (to_close)
	{
		if (to_close[0] > 2)
			close (to_close[0]);
		if (to_close[1] > 2)
			close (to_close[1]);
	}
	if (shell)
	{
		shell->exit_status = 1;
		_p_err(shell->cmd, (char *[3]){strerror(errno), "dup", ""}, exit);
	}
}
