/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:20:24 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/21 13:18:00 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__ctrl_d(t_shell *shell)
{
	clair_env(&shell->env_lst);
	ft_malloc(0, 0);
	printf("exit\n");
	exit(0);
}

void	print_sruct(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	while (tmp)
	{
		i = 0;
		printf("cmd: %s\n", tmp->path);
		write(1, "args: ", 6);
		while (tmp->args && tmp->args[i])
		{
			write(1, tmp->args[i], ft_strlen(tmp->args[i]));
			write(1, " ", 1);
			i++;
		}
		printf("\n");
		if (!tmp->args)
			printf("args: NULL\n");
		while (tmp->redir)
		{
			printf("redir: %s\n", tmp->redir->file);
			tmp->redir = tmp->redir->next;
		}
		tmp = tmp->next;
	}
}

void	print_line(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->join == IS_JOINBLE)
			printf("data: %s\tIS_JOINBLE\n", tmp->data);
		else
			printf("data: %s\ttype: %d\tstate: %d\tjoin: %d\n",
				tmp->data, tmp->type, tmp->state, tmp->join);
		tmp = tmp->next;
	}

}
void	interpreter(t_shell *shell, char *line)
{
	if (g_recv_signal == 1)
	{
		shell->exit_status = 1;
		g_recv_signal = 0;
	}
	add_history(line);
	ft_tokenize(line, shell);
	// print_line(shell->tokens);
	ft_parser(shell);
	ft_expand(shell);
	redirection(shell);
	print_sruct(shell->cmd);
}

void	mini_shell(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			__ctrl_d(shell);
		interpreter(shell, line);
		ft_malloc(0, 0);
		shell->tokens = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	ft_signal();
	ft_memset(&shell, 0, sizeof(t_shell));
	shell.env = env;
	shell.env_lst = ft_get_env(env);
	if (!shell.env_lst)
		return (1);
	mini_shell(&shell);
}
