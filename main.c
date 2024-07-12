/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:20:24 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/12 16:24:57 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void print_line(t_token *head)
// {
// 	while (head)
// 	{
// 		printf("[data: %s]\t [type: %d]\t [state: %d]\n",
// head->data, head->type, head->state);
// 		head = head -> next;
// 	}
// }
	// print_line(token);

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
			ft_malloc (0, 0);
			free(line);
			break ;
		}
		add_history(line);
		ft_tokenize(line, &token);
		ft_malloc(0, 0);
		token = NULL;
		free(line);
	}
	return (0);
}

int	main(void)
{
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, new_prompt);
	read_line();
}
