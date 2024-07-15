/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 07:48:29 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/15 20:37:37 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# define READ "\033[1;31m"
# define END "\033[0m"

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HERE,
}			t_type;

typedef enum e_state
{
	DEFAULT,
	IN_SINGALE,
	IN_DOUBLE,
	DOLLAR,
}			t_state;

typedef struct s_token
{
	t_type			type;
	t_state			state;
	char			*data;
	struct s_token	*next;
}				t_token;

int		is_special(char c);
int		lstsize(t_token *lst);
void	ft_parser(t_token **tokens);
void	ft_tokenize(char *line, t_token **head);
void	add_lst(char *content, t_token **lst, t_state state);
void	opertor_delimiter(char *token, int *i, t_token **head, t_state state);
void	word_delimiter(char *token, int *i, t_token **head, t_state state);
void	dollar_delimiter(char *token, int *i, t_token **head, t_state state);
int		quote_delimiter(char *token, int *i, t_token **head, t_state state);

#endif