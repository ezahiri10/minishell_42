NAME = minishell

CC = cc

RM = rm -f

FLAGS = -Wall -Wextra -Werror

SRC = main.c tokenization.c ft_list.c

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


	
