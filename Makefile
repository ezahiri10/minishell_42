NAME = minishell

CC =  cc  -fsanitize=address -g

RM = rm -f

FLAGS = -Wall -Wextra -Werror

SRC = 	ft_env_lst.c expander.c ft_get_env.c lst_cmd.c \
		list_redir.c  minishell.c creat_cmd.c\
		token_dilemeter.c ft_list.c parser.c \
		ft_signal.c tokenizer.c utils.c redirection.c \
		here_doc.c expand_herdoc.c printiing_func.c ft_exit.c \

OBG = $(SRC:.c=.o)

LIBFT = libft/libft.a

all : $(LIBFT) $(NAME) 

$(LIBFT) : 
	@make -C libft/

	
$(NAME) : $(OBG)
	$(CC) $(FLAGS) -lreadline $(OBG) $(LIBFT) -o $(NAME)

%.o : %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean :
	@make -C  libft/ clean
	$(RM) $(OBG)

fclean : clean 
	@make -C libft/ fclean
	$(RM) $(NAME)

re : fclean all
