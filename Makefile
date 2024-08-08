NAME = minishell

CC =  cc  -fsanitize=address -g

RM = rm -f

FLAGS = -Wall -Wextra -Werror

SRC = 	expanding/expander.c expanding/heredoc_expansion.c env/env_lst.c env/set_env.c env/utils_env.c\
		build_struct/cmd_lst.c expanding/ft_expansion.c env/get_env.c env/inisailise_env.c execution/child_handler.c\
		parsing/token_list.c build_struct/redirection_lst.c  src/minishell.c execution/check_redirection.c\
		parsing/here_doc.c  printiing_func.c src/ft_exit.c build_struct/def_cmd_type.c execution/redirections.c\
		parsing/token_dilemeter.c  parsing/parser.c utils/utils.c execution/executer.c execution/parce_cmd.c\
		src/ft_signal.c parsing/tokenizer.c build_struct/get_pipeline.c execution/builtin_exec.c\
		build_struct/create_cmd.c parsing/syntax_error.c build_struct/join_words.c \
		env/sort_print_env.c built_in/cd.c built_in/echo.c built_in/env.c built_in/exit.c built_in/export.c \
		built_in/pwd.c built_in/unset.c build_struct/check_ambiguous.c

OBG = $(SRC:%.c= %.o)

LIBFT = libft/libft.a

all : $(LIBFT) $(NAME) 

$(LIBFT) : 
	@make -C libft/

$(NAME) : $(OBG)
	$(CC) $(FLAGS) -lreadline $(OBG) $(LIBFT) -o $(NAME)

obj/%.o : %.c minishell.h
	$(CC) $(FLAGS) -I. -c $< -o $@

clean :
	@make -C  libft/ clean
	$(RM) $(OBG)

fclean : clean 
	@make -C libft/ fclean
	$(RM) $(NAME)

re : fclean all
