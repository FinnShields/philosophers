CC		= cc
CFLAGS	= -Wall -Werror -Wextra
NAME	= philo
SRC		= main.c init.c utils1.c utils2.c philo_routine.c \
			threads.c status_monitor.c
OBJ		= $(SRC:.c=.o)
HEADER	= philo.h

%.o:		%.c
				@$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ) $(HEADER)
				@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
				@echo "compiled!"

clean:
				@rm -f $(OBJ)
				@echo "cleaned!"

fclean:		clean
				@rm -f $(NAME)
				@echo "fcleaned!"

re:			fclean all

.PHONY:		all clean fclean re