# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fwahl <fwahl@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/29 17:00:18 by fwahl             #+#    #+#              #
#    Updated: 2026/08/29 17:00:18 by fwahl            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
# CFLAGS	+=	-Ofast
# CFLAGS	+=	-fsanitize=address -g
LDFLAGS	=	-ldl -lglfw -pthread -lm
RM		=	rm -rf
MLX_URL =	https://github.com/codam-coding-college/MLX42.git

NAME	=	fdf
SRCS	=	./src/main.c \
			./src/parse.c \
			./src/map.c \
			./src/utils.c \
			./src/draw.c \
			./src/project.c
			
OBJS	=	$(SRCS:.c=.o)
HEADERS	=	./include/fdf.h

LIBFT	=	./libft/libft.a
MLX42	=	./MLX42/build/libmlx42.a

RESET	=	\x1b[0m
RED		=	\x1b[31m
YELLOW	=	\x1b[33m
BLUE	=	\x1b[34m

all: $(LIBFT) $(MLX42) $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42) $(LDFLAGS) -o $@
	@echo "$(BLUE) $(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42) $(LDFLAGS) -o $@ $(RESET)"
	@echo "$(YELLOW)Creating executable finished.$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE) $(CC) $(CFLAGS) -c $< -o $@ $(RESET)"
	@echo "$(YELLOW)Creating object file finished.$(RESET)"

$(LIBFT):
	@git submodule init
	@git submodule update --remote
	@$(MAKE) -C ./libft

$(MLX42):
	@if [ ! -d "./MLX42" ]; then \
		git clone $(MLX_URL) ./MLX42; \
	fi
	@cmake ./MLX42 -B ./MLX42/build
	@cmake --build ./MLX42/build

bonus: CFLAGS += -D BONUS=1
bonus: all

clean:
	@$(RM) $(OBJS)
	@echo "$(RED) $(RM) $(OBJS) $(RESET)"
	@echo "$(YELLOW)Deleting object files finished.$(RESET)"

	@$(RM) ./MLX42/build
	@echo "$(RED) $(RM) ./MLX42/build $(RESET)"
	@echo "$(YELLOW)Deleting MLX42 files finished.$(RESET)"

	@$(MAKE) clean -C ./libft

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED) $(RM) $(NAME) $(RESET)"
	@echo "$(YELLOW)Deleting executable finished.$(RESET)"

	@$(MAKE) fclean -C ./libft

re: fclean
	@$(MAKE) all

.PHONY: all clean fclean re