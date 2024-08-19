NAME = minishell

CC =  cc  -fsanitize=address -g

RM = rm -f

FLAGS = -Wall -Wextra -Werror

LINKING_LIB = -lreadline -Llibft -lft

SRC =	expanding/heredoc_expansion.c expanding/expander.c expanding/ft_expansion.c \
		parsing/token_list.c parsing/here_doc.c parsing/token_dilemeter.c parsing/parser.c \
		parsing/tokenizer.c parsing/syntax_error.c built_in/cd.c built_in/echo.c built_in/exit.c \
		built_in/export.c built_in/env.c built_in/unset.c built_in/pwd.c env/get_env.c env/env_lst.c \
		env/sort_print_env.c env/inisailise_env.c env/set_env.c env/utils_env.c build_struct/cmd_lst.c \
		build_struct/redirection_lst.c build_struct/def_cmd_type.c build_struct/check_ambiguous.c  \
		build_struct/create_cmd.c build_struct/get_pipeline.c build_struct/join_words.c    \
 		execution/check_redirection.c execution/child_handler.c execution/redirections.c  \
		execution/parce_cmd.c execution/executer.c execution/builtin_exec.c src/ft_exit.c \
		src/minishell.c src/ft_signal.c utils/utils.c utils/edit_strings.c

OBG = $(SRC:%.c= %.o)

LIBFT = libft

all : $(LIBFT) $(NAME) 

$(LIBFT) : 
	@make -sC libft/

$(NAME) : $(OBG)
	$(CC) $(FLAGS) $(LINKING_LIB) $(OBG) -o $(NAME)

%.o : %.c minishell.h
	$(CC) $(FLAGS) -I. -Ilibft -c $< -o $@

clean :
	@make -C  libft/ clean
	$(RM) $(OBG)

fclean : clean 
	@make -C libft/ fclean
	$(RM) $(NAME)

re : fclean all

.PHONY: libft
