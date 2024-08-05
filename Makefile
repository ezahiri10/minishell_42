NAME = minishell

CC =  cc  -fsanitize=address -g

RM = rm -f

FLAGS = -Wall -Wextra -Werror

SRC = 	src/env_lst.c expanding/expander.c expanding/heredoc_expansion.c execution/redirections.c execution/parce_cmd.c \
		src/get_env.c build_struct/cmd_lst.c expanding/ft_expansion.c execution/child_handler.c\
		parsing/token_list.c build_struct/redirection_lst.c  src/minishell.c utils/utils1.c\
		parsing/here_doc.c  printiing_func.c src/ft_exit.c build_struct/def_cmd_type.c\
		parsing/token_dilemeter.c  parsing/parser.c  execution/executer.c execution/check_redirection.c \
		src/ft_signal.c parsing/tokenizer.c build_struct/get_pipeline.c utils/utils.c\
		build_struct/create_cmd.c parsing/syntax_error.c build_struct/join_words.c 

OBG = $(SRC:%.c=obj/%.o)

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
