/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 07:48:29 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/16 18:41:59 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/errno.h>
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
	int				err;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_shell
{
	t_env	*env_lst;
	char	**env;
	t_token	*tokens;
	int		exit_status;
}				t_shell;

void	ft_parser(t_shell *shell);
int		is_special(char c);
int		lstsize(t_token *lst);
void	ft_tokenize(char *line, t_token **head);
void	add_lst(char *content, t_token **lst, t_state state);
void	ft_expand(t_shell *shell);
void	opertor_delimiter(char *token, int *i, t_token **head, t_state state);
void	word_delimiter(char *token, int *i, t_token **head, t_state state);
void	dollar_delimiter(char *token, int *i, t_token **head, t_state state);
int		quote_delimiter(char *token, int *i, t_token **head, t_state state);
void	*add_env(char *var, char *value, t_env **head);
void	clair_env(t_env **head);
t_env	*ft_get_env(char **env);
void	ft_signal();


#endif