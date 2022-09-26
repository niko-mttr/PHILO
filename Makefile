# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/02 09:45:23 by nmattera          #+#    #+#              #
#    Updated: 2022/09/26 16:48:11 by nmattera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRC 	=	src/main.c\
			src/philo_parsing.c\
			src/philo_end.c\
			src/philo_utils.c\
			src/philo_time.c\
			src/philo_init.c\
			src/philo_solo.c

OBJS 	=	${SRC:.c=.o}

CC 		=	gcc
CFLAGS 	=	-Wall -Wextra -Werror -pthread -fsanitize=thread -g

INCLUDES =	-I includes

.c.o:
		@${CC} ${CFLAGS} ${INCLUDES} -c -o $@ $<

all: 	${NAME}

${NAME}: ${OBJS}
		@$(CC) $(CFLAGS) ${OBJS} ${INCLUDES} -o ${NAME}
		@echo "Philo compiled!\n"

clean:
		@rm -f ${OBJS}

fclean: clean
		@rm -f $(NAME)
		@echo "Deleting EVERYTHING!"

re:		fclean all

.PHONY: all clean fclean re
