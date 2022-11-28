# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 16:15:21 by viferrei          #+#    #+#              #
#    Updated: 2022/11/28 10:29:06 by viferrei         ###   ########.fr        #
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
				ft_atoi.c \
				main.c \
				state_utils.c \
				state.c \
				tests.c
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
