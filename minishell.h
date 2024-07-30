/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 07:48:29 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/30 20:07:52 by alafdili         ###   ########.fr       */
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

# define FAILURE 1
# define SUCCESS 0

# define READ "\033[1;31m"
# define YEL "\033[32m"
# define END "\033[0m"

// export x="""ls"

extern int	g_recv_signal;

typedef enum e_type
{
	ERROR,
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HERE_DOC,
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
	int		fd;
	char	*origin;
	char	*content;
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
	t_type			type;
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd
{
	bool			type;
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
	int		stoped;
	int		input;
	int		exit_status;
}				t_shell;

void	ft_signal(void);
t_join	is_joinble(char c);
int		is_special(char c);
t_env	*ft_get_env(char **env);
void	clair_env(t_env **head);
char	*char_to_string(char c);
void	close_fd(t_shell *shell);
void	clean_up(t_shell *shell);
void	expander(t_shell *shell);
int		ft_count(char *str, char c);
void	get_pipeline(t_shell *shell);
void	cmd_type_def(t_shell *shell);
void	display_error(t_shell *shell);
char	*limiter(int *i, char *token);
char	*limiter(int *i, char *token);
bool	check_is_double(t_token *tmp);
void	tokenizer(char *line, t_shell *shell);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
char	*set_value(char *__name, t_env *__env);
void	parser(t_shell *shell, t_token *tokens);
t_cmd	*create_cmd(char *to_join, t_redir *redir);
void	join_word(char **to_join, t_token **start);
char	*search_dollar(t_shell *shell, char *token);
char	*dollar_expansion(char *tmp, t_shell *shell);
void	heredoc_expansion(t_shell *shell, int *old_fd);
void	*add_env(char *var, char *value, t_env **head);
t_cmd	*new_cmd(char *cmd, t_redir *redir, char **args);
void	space_to_127(t_token *token, t_state check_with);
void	join_export_word(char **to_join, t_token **start);
bool	here_doc(t_shell *shell, t_token *head, int input);
void	add_redir(t_redir **lst, char *file, t_type type, int fd);
void	get_cmd_part(t_token **head, t_redir **redir, char **args);
int		check_and_join(char **filename, t_token *token, t_type *type);
void	syntax_error_check(t_shell *shell, t_token *limiter, int flag);
void	add_lst(char *content, t_token **lst, t_state state, t_join join);
void	word_delimiter(char *token, int *i, t_token **head, t_state state);
int		quote_delimiter(char *token, int *i, t_shell *shell, t_state state);
void	dollar_delimiter(char *token, int *i, t_token **head, t_state state);
void	opertor_delimiter(char *token, int *i, t_token **head, t_state state);

// printing functions
void	print_sruct(t_shell *shell);
void	print_line(t_shell *shell);
void	print_here_doc(t_shell *shell);

#endif