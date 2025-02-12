# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/26 18:50:07 by emgenc            #+#    #+#              #
#    Updated: 2025/02/12 15:35:37 by emgenc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## %.o: %.c
##	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@
## $(NAME): $(OBJ)
##	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

NAME			= fractol

SOURCES			= fractol.c
OBJECTS			= ${SOURCES:.c=.o}

SOURCES_BONUS	= 
OBJECTS_BONUS	= ${SOURCES_BONUS:.c=.o}

CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror

all:	${NAME}

${NAME}:	${OBJECTS}
	@$(CC) ${OBJECTS} -Lminilibx-linux -lmlx -o ${NAME}

bonus:	${OBJECTS_BONUS}
	@$(CC) ${OBJECTS_BONUS} -Lminilibx-linux -lmlx -o ${NAME}

clean:
	@rm -rf ${OBJECTS} ${OBJECTS_BONUS}

fclean:	clean
	@rm -rf ${NAME}

re:	fclean all

exec:
	@make fclean && make && make bonus && make clean && clear
	@echo "fract-ol: Compilation finished.\nReady!"

.PHONY:	all bonus clean fclean re exec