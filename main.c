/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:20:24 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/16 19:15:07 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_line(t_token *head)
{
	while (head)
	{
		printf("[data: %s]\t [type: %d]\t [state: %d]\n",
			head->data, head->type, head->state);
		head = head -> next;
	}
}

int	read_line(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_malloc(0, 0);
			printf ("exit\n");
			break ;
		}
		add_history(line);
		ft_tokenize(line, &shell->tokens);
		print_line(shell->tokens);
		ft_parser(shell);
		printf ("------------------------------------------\n");
		ft_expand(shell);
		print_line(shell->tokens);
		ft_malloc(0, 0);
		shell->tokens = NULL;
	}
	return (0);
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
	read_line(&shell);
}
