/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:13:21 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/17 16:08:39 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_value(char *__name, t_env *__env)
{
	int	len;

	while (__env)
	{
		len = ft_strlen(__env->var);
		if (!ft_strcmp(__name, __env->var))
			return (ft_strdup(__env->value));
		__env = __env->next;
	}
	return (ft_strdup(""));
}

char	*dollar_expansion(char *tmp, t_shell *shell)
{
	char *str;
	
	if (ft_strlen (tmp) == 1)
		return (tmp);
	else if (tmp[1] == '?')
		return (ft_strjoin (ft_itoa(shell->exit_status), tmp + 2));
	else
	{
		str = set_value(tmp + 1, shell->env_lst);
		return (str);
	}
}

char	*limiter(int *i, char *token)
{
	int	start;
	char *rvalue;
	int	end;
	int	id;

	start = *i;
	end = start + 1;
	id = 0;
	
	if (token[end] == '?')
		end++;
	while (token[end] && (ft_isalnum(token[end]) || token[end] == '_'))
		end++;
	*i = end;
	rvalue = ft_substr(token, start, *i - start);
	printf("rvalue = %s\n", rvalue);
	return (rvalue);
}

char *char_to_string(char c)
{
	char *dest;

	dest = ft_malloc(sizeof(char) * 2, 1);
	dest[0] = c;
	dest[1] = '\0';
	return (dest);
}

char	*search_dollar(t_shell *shell, char *token)
{
	int end;
	char *to_join;

	to_join = NULL;
	end = 0;
	while (token[end])
	{
		if (token[end] == '$')
		{
			to_join = ft_strjoin(to_join, dollar_expansion(limiter(&end, token), shell));
		}
		else
			to_join = ft_strjoin(to_join, char_to_string(token[end++]));
	}
	return (to_join);
}

void	ft_expand(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->state == DOLLAR)
			tmp->data = dollar_expansion(tmp->data, shell);
		else if (tmp->state == IN_DOUBLE)
			tmp->data = search_dollar(shell, tmp->data);
		tmp = tmp->next;
	}
}
