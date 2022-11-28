# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 16:15:21 by viferrei          #+#    #+#              #
#    Updated: 2022/11/28 19:46:27 by viferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g -pthread

# valgrind flags.
LFLAGS		=	--tool=helgrind --tool=drd \
				./philo 4 310 200 100

OBJDIR		= ./objs/

SRC			= check_input.c \
				eat_utils.c \
				ft_atoi.c \
				init.c \
				main.c \
				state_done_utils.c \
				state_is_utils.c \
				state.c
OBJ			= $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(OBJDIR)%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

leaks:
	valgrind $(LFLAGS)

git:
	git add ../
	git commit -m"make git"
	git push

.PHONY: all clean fclean re leaks run
