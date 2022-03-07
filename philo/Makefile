# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 17:14:10 by bsavinel          #+#    #+#              #
#    Updated: 2022/03/04 13:39:01 by bsavinel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS_DIR =	objs/

SRCS_DIR =	srcs/

SRCS =	srcs/death.c			\
		srcs/end_tools.c		\
		srcs/end.c				\
		srcs/init_struct.c		\
		srcs/main.c				\
		srcs/philo_mini_utils.c	\
		srcs/philo_utils.c		\
		srcs/routine.c			\
		srcs/take_and_drop.c

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEPS = $(addprefix $(OBJS_SRCS), $(SRCS:.c=.d))

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -f

INCS = -I includes

NAME = philo

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCS)

%.o: %.c
	$(CC) $(CFLAGS) - -c $< -o $@ $(INCS)

clean :
	$(RM) $(OBJS) $(DEPS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

-include $(DEPS)

.PHONY: all clean fclean re