/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:56:31 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/26 15:56:54 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_is_double(t_token *tmp)
{
	while (tmp && tmp->join == JOINBLE)
	{
		if (tmp->state == IN_SINGALE || tmp->state == IN_DOUBLE)
			return (true);
		tmp = tmp->next;
	}
	if (tmp->state == IN_SINGALE || tmp->state == IN_DOUBLE)
		return (true);
	return (false);
}

char	*set_value(char *__name, t_env *__env)
{
	while (__env)
	{
		if (!ft_strcmp(__name, __env->var))
			return (ft_strdup(__env->value));
		__env = __env->next;
	}
	return (ft_strdup(""));
}

char	*dollar_expansion(char *tmp, t_shell *shell)
{
	char	*str;
	int		count;
	int		len;

	len = ft_strlen(tmp);
	count = ft_count(tmp, '$');
	if (count % 2 == 0 || count == len || len == 1)
		return (tmp);
	else if (tmp[count] == '?')
	{
		str = ft_itoa(shell->exit_status);
		while (--count)
			str = ft_strjoin("$", str);
		return (str);
	}
	else if (count % 2)
	{
		str = set_value(tmp + count, shell->env_lst);
		while (--count)
			str = ft_strjoin("$", str);
		return (str);
	}
	return (NULL);
}

char	*limiter(int *i, char *token)
{
	int	start;
	int	end;

	start = *i;
	end = start + 1;
	while (token[end] == '$')
		end++;
	if (token[end] == '?')
		end++;
	while (token[end] && (ft_isalnum(token[end]) || token[end] == '_'))
		end++;
	*i = end;
	return (ft_substr(token, start, *i - start));
}

char	*search_dollar(t_shell *shell, char *token)
{
	int		end;
	char	*to_join;
	char	*expanded;

	to_join = NULL;
	end = 0;
	if (!token[0])
		return (token);
	while (token[end])
	{
		if (token[end] == '$')
		{
			expanded = dollar_expansion(limiter(&end, token), shell);
			to_join = ft_strjoin(to_join, expanded);
		}
		else
		{
			to_join = ft_strjoin(to_join, char_to_string(token[end]));
			end++;
		}
	}
	return (to_join);
}
