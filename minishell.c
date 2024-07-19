/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:20:24 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/19 18:11:55 by ezahiri          ###   ########.fr       */
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
		printf("path: %s\n", tmp->path);
		printf("args: ");
		i = 0;
		while (tmp->args[i])
		{
			printf("%s ", tmp->args[i]);
			i++;
		}
		printf("\nredir: \n");
		while (tmp->redir)
		{
			printf("[filename: %s]\t[type: %d]\n",
				tmp->redir->file, tmp->redir->type);
			tmp->redir = tmp->redir->next;
		}
		printf("-------------------------\n");
		tmp = tmp->next;
	}
}

// void	print_line(t_token *head)
// {
// 	while (head)
// 	{
// 		printf("[data: %s]\t [type: %d]\t [state: %d]\n",
// 			head->data, head->type, head->state);
// 		head = head -> next;
// 	}
// }
// print_line(shell->tokens);

void	interpreter(t_shell *shell, char *line)
{
	if (g_recv_signal == 1)
	{
		shell->exit_status = 1;
		g_recv_signal = 0;
	}
	add_history(line);
	ft_tokenize(line, shell);
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
