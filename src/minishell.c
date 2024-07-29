/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:20:24 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/29 21:42:17 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_recv_signal = 0;

void	__ctrl_d(t_shell *shell)
{
	close(shell->input);
	close_fd(shell);
	clair_env(&shell->env_lst);
	ft_malloc(0, 0);
	printf("\x1b[FMinishell$ exit\n");
	exit(0);
}

void	interpreter(t_shell *shell, char *line)
{
	if (g_recv_signal == SIGINT)
	{
		shell->exit_status = 1;
		g_recv_signal = 0;
	}
	add_history(line);
	tokenizer(line, shell);
	parser(shell, shell->tokens);
	expander(shell);
	get_pipeline(shell);
	print_sruct(shell);
	close_fd(shell);
}

void	mini_shell(t_shell *shell)
{
	char	*line;

	shell->input = dup(0);
	while (1)
	{
		shell->stoped = 0;
		line = readline("Minishell$ ");
		if (!line && g_recv_signal == SIGINT)
		{
			dup2(shell->input, 0);
			shell->exit_status = 1;
			g_recv_signal = 0;
			continue ;
		}
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
