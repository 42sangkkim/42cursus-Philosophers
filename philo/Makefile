# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 14:26:23 by sangkkim          #+#    #+#              #
#    Updated: 2022/08/27 16:26:25 by sangkkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = main.c init_simulation.c observer_main.c utils.c \
	   philo_main.c philo_echo.c philo_wait.c
INCS = philo.h

CC = cc
CFLAGS = -Wall -Wextra -Werror

$(NAME) : $(SRCS) $(INCS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

.PHONY : all clean fclean re

all : $(NAME)

clean :

fclean : clean
	rm -f $(NAME)

re : fclean all
