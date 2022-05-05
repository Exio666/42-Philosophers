# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 17:14:10 by bsavinel          #+#    #+#              #
#    Updated: 2022/03/04 12:35:41 by bsavinel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	srcs/death.c			\
		srcs/end_tools.c		\
		srcs/end.c				\
		srcs/init_struct.c		\
		srcs/main.c				\
		srcs/philo_mini_utils.c	\
		srcs/philo_utils.c		\
		srcs/routine.c			\
		srcs/take_and_drop.c

OBJS = $(SRCS:.c=.o)

DEPS = $(SRCS:.c=.d)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -MMD -pthread#-g3 -fsanitize=thread

RM = rm -f

INCS = -I includes

NAME = philo

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

clean :
	$(RM) $(OBJS) $(DEPS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

-include $(DEPS)

.PHONY: all clean fclean re