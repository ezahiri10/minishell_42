NAME = minishell

CC =  cc -fsanitize=address -g

RM = rm -f

FLAGS = -Wall -Wextra -Werror

SRC = 	ft_env_lst.c ft_expand.c ft_get_env.c  lst_cmd.c lisrt_redir.c\
		list_size.c minishell.c token_dilemeter.c \
		ft_list.c ft_parser.c ft_signal.c \
		tokenizer.c utils.c redirection.c \

OBG = $(SRC:.c=.o)

LIBFT = libft/libft.a

all : $(LIBFT) $(NAME) 

$(LIBFT) : 
	@make -C libft/

%.o : %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@
	
$(NAME) : $(OBG)
	$(CC) $(FLAGS) -lreadline $(OBG) $(LIBFT) -o $(NAME)


clean :
	@make -C  libft/ clean
	$(RM) $(OBG)

fclean : clean 
	@make -C libft/ fclean
	$(RM) $(NAME)

re : fclean all
