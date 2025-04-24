# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/13 00:05:40 by emgenc            #+#    #+#              #
#    Updated: 2025/04/14 15:20:44 by emgenc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
NAME_BONUS = fractol_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_FILE = ./minilibx/libmlx_Linux.a
LIBFT = ./libft-emgenc/libft.a

SOURCE_FILES = fractol.c util.c util2.c atod.c
OBJECT_FILES = $(SOURCE_FILES:.c=.o)

BONUS_SFILES = fractol_bonus.c util_bonus.c util2_bonus.c atod.c
BONUS_OFILES = $(BONUS_SFILES:.c=.o)

all: $(MLX_FILE) $(LIBFT) $(NAME)

$(MLX_FILE):
	@git clone https://github.com/42paris/minilibx-linux.git ./minilibx
	@make -C ./minilibx

$(LIBFT):
	@make -C ./libft-emgenc

$(NAME): $(OBJECT_FILES)
	@${CC} ${OBJECT_FILES} ${LIBFT} ${MLX_FILE} -Lminilibx -lmlx_Linux -lX11 -lm -lXext -o ${NAME}

bonus: $(MLX_FILE) $(LIBFT) $(NAME_BONUS)

$(NAME_BONUS): $(BONUS_OFILES)
	@${CC} ${BONUS_OFILES} ${LIBFT} ${MLX_FILE} -Lminilibx -lmlx_Linux -lX11 -lm -lXext -o ${NAME_BONUS}

clean:
	@make clean -C ./libft-emgenc
	@rm -rf ${OBJECT_FILES} ${BONUS_OFILES}

fclean: clean
	@make fclean -C ./libft-emgenc
	@rm -rf ./minilibx
	@rm -rf ${NAME} ${NAME_BONUS}
	@rm -rf ${OBJECT_FILES} ${BONUS_OFILES}

re: fclean all

exec:
	@make fclean && make && make clean && clear
	@echo "fractol: Compilation finished.\nReady!"

.PHONY: all clean fclean exec bonus re
