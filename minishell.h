/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 07:48:29 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/21 20:47:30 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

#define FAILURE 1
#define SUCCESS 0

# define READ "\033[1;31m"
# define YEL "\033[32m"
# define END "\033[0m"

int	g_recv_signal;

typedef enum e_type
{
	ERROR,
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

typedef enum e_joinble
{
	JOINBLE,
	NON_JOINBLE,
}			t_join;

typedef struct s_token_data
{
	char	*content;
	int		fd;
}	t_data;

typedef struct s_token
{
	t_type			type;
	t_state			state;
	t_join			join;
	t_data			data;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_redir
{
	int				fd;	
	char			*file;
	int				type;
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd
{
	char			*path;
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_shell
{
	t_env	*env_lst;
	char	**env;
	t_token	*tokens;
	t_cmd	*cmd;
	int		exit_status;
}				t_shell;

void	ft_signal(void);
t_join	is_joinble(char c);
int		is_special(char c);
int		lstsize(t_token *lst);
bool	here_doc(t_shell *shell);
char	*char_to_string(char c);
t_env	*ft_get_env(char **env);
void	clair_env(t_env **head);
void	ft_expand(t_shell *shell);
void	ft_parser(t_shell *shell);
void	redirection(t_shell *shell);
int		ft_count(char *str, char c);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
void	ft_tokenize(char *line, t_shell *shell);
void	*add_env(char *var, char *value, t_env **head);
t_cmd	*new_cmd(char *cmd, t_redir *redir, char **args);
void	add_redir(t_redir **lst, char *file, t_type type);
void	add_lst(char *content, t_token **lst, t_state state, t_join join);
void	word_delimiter(char *token, int *i, t_token **head, t_state state);
void	opertor_delimiter(char *token, int *i, t_token **head, t_state state);
void	dollar_delimiter(char *token, int *i, t_token **head, t_state state);
int		quote_delimiter(char *token, int *i, t_shell *shell, t_state state);

#endif