/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:13:21 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/17 00:55:09 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_value(char *__name, t_env *__env)
{
	int	len;

	while (__env)
	{
		len = ft_strlen(__env->var);
		if (!ft_strncmp(__name, __env->var, len))
			return (ft_strdup(__env->value));
		__env = __env->next;
	}
	return (ft_strdup(""));
}

void	dollar_expansion(t_token *tmp, t_shell *shell)
{
	if (ft_strlen (tmp->data) == 1)
		return ;
	else if (tmp->data[1] == '?')
		tmp->data = ft_strjoin (ft_itoa(shell->exit_status), tmp->data + 2);
	else
		tmp->data = set_value(tmp->data + 1, shell->env_lst);
	return ;
}

char	*limiter(int *i, char *token)
{
	int	start;
	int	end;
	int	id;

	start = *i + 1;
	end = start;
	id = 0;
	while (token[end] && (ft_isalnum(token[end]) || token[end] == '_'
		|| token[end] == '?' ))
		end++;
	*i = end;
	return (ft_substr(token, start, *i - start + 1));
}

char	*search_dollar(t_shell *shell, char *token)
{
	int		i;
	char	*to_join;
	char	*s1;
	char	*s2;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
		{
			printf ("|%d|\n", i);
			if (token[i + 1] == '?')
			{
				// printf ("salam\n");
				printf ("token == %s\n", token + i + 2);
				token = ft_strjoin (ft_itoa(shell->exit_status), token + i + 2);
				sleep(1);
				printf ("token == %s\n", token + i + 2);
				i = 0;
			}
			else
			{
			if (i == 0)
				s1 = ft_strdup("");
			else
				s1 = ft_substr(token, 0, i);
			to_join = limiter(&i, token);
			to_join = set_value(to_join, shell->env_lst);
			s2 = ft_substr(token, i, ft_strlen(token));
			token = ft_strjoin(s1, to_join);
			token = ft_strjoin(token, s2);
			}
			i = 0;
		}
		i++;
	}
	return (token);
}

void	ft_expand(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->state == DOLLAR)
			dollar_expansion(tmp, shell);
		else if (tmp->state == IN_DOUBLE)
			tmp->data = search_dollar(shell, tmp->data);
		tmp = tmp->next;
	}
}
