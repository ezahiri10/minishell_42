/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:20:24 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/22 18:57:51 by alafdili         ###   ########.fr       */
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

void	print_sruct(t_shell *shell)
{
	t_cmd	*tmp;
	int		i;

	if (!shell)
		return ;
	tmp = shell->cmd;
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

void print_line(t_shell *shell)
{
	t_token *head;

	head = shell->tokens;
	
	while (head)
	{
		printf("data [%s]\n", head->data.content);
		head = head->next;
	}
}

void print_here_doc(t_shell *shell)
{
	t_token *token;
	char 	*line;
	int i;

	if (!shell)
		return ;
	i = 0;
	token = shell->tokens;
	while (token)
	{
		if (!ft_strcmp(token->data.content, "<<"))
		{
			printf(""YEL"here_doc [%d]"END"\n", i + 1);
			while (1)
			{
				line = get_next_line(token->data.fd);
				if (!line)
					break ;
				printf("%s", line);
			}
			i++;
		}
		token = token->next;
	}
}

void	interpreter(t_shell *shell, char *line)
{
	if (g_recv_signal == SIGINT)
	{
		shell->exit_status = 1;
		g_recv_signal = 0;
	}
	add_history(line);
	ft_tokenize(line, shell);
	ft_parser(shell);
	// print_line(shell);
	// print_here_doc(shell);
	// ft_expand(shell);
	// redirection(shell);
	// print_sruct(shell->cmd);
}

void	mini_shell(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("Minishell$ ");
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
