/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:20:24 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/15 22:23:33 by alafdili         ###   ########.fr       */
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

void	new_prompt(int s)
{
	if (s == SIGINT)
		printf ("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	read_line(void)
{
	char	*line;
	t_token	*token;

	token = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf ("exit\n");
			break ;
		}
		add_history(line);
		ft_tokenize(line, &token);
		print_line(token);
		ft_parser(&token);
		ft_malloc(0, 0);
		token = NULL;
	}
	return (0);
}

int	main(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	read_line();
}
