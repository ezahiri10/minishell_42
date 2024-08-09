/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:30:51 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/09 19:06:33 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (true);
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (false);
	i++;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	value_non_joinlble(char *name, char *value, t_shell *shell, int flag)
{
	t_env	*tmp;

	tmp = shell->env_lst;
	if (exist_env(name, shell->env_lst) == true)
	{
		if (flag == 0)
			return ;
		while (tmp)
		{
			if (ft_strcmp(tmp->var, name) == 0)
			{
				tmp->value = value;
				break ;
			}
			tmp = tmp->next;
		}
	}
	else
	{
		if (!add_env(name, value, &shell->env_lst))
			clean_up(shell);
	}
}

void	value_joinble(char *name, char *value, t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env_lst;
	if (exist_env(name, shell->env_lst) == true)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->var, name) == 0)
			{
				tmp->value = join_env(tmp->value, value);
				if (!tmp->value)
					clean_up(shell);
				break ;
			}
			tmp = tmp->next;
		}
	}
	else
	{
		if (!add_env(name, value, &shell->env_lst))
			clean_up(shell);
	}
}

bool	check_type(char *arg, char **name, char **value, int *flag)
{
	int	pos;

	if (arg[0] == '\0' || arg[0] == '=' || arg[0] == '+')
		return (false);
	pos = researcher(arg, '=');
	if (pos == 0)
	{
		*name = dup_env(arg);
		if (!*name)
			*flag = -1;
		*value = NULL;
		*flag = 0;
	}
	else
	{
		*value = subenv(arg, pos + 1, ft_strlen(arg));
		if (arg[pos - 1] == '+' && --pos)
			*flag = 2;
		else
			*flag = 1;
		*name = subenv(arg, 0, pos);
		if (!*value || !*name)
			*flag = -1;
	}
	return (is_valid(*name));
}

void	set_env(t_shell *shell, char *arg)
{
	char	*name;
	char	*value;
	int		flag;

	if (check_type(arg, &name, &value, &flag) == true)
	{
		if (flag == -1)
			clean_up(shell);
		else if (flag == 0 || flag == 1)
			value_non_joinlble(name, value, shell, flag);
		else if (flag == 2)
			value_joinble(name, value, shell);
	}
	else
	{
		ft_export_error(arg, shell);
		return ;
	}
}
