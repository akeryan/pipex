# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/14 19:39:20 by akeryan           #+#    #+#              #
#    Updated: 2023/12/23 15:43:46 by akeryan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
FLAGS		= -Wall -Wextra -Werror
LINKS		= -Ilibft -Ift_printf -Llibft -Lft_printf -lft -lftprintf

SRC_DIR		= src
LIBFT_DIR	= libft
FT_PRINT_DIR = ft_printf
MANDATORY	= pipex.c path.c error.c parsing.c init.c clean.c utils.c main.c split_cmd.c
CC			= cc


OBJ = $(patsubst %.c, %.o, $(MANDATORY))

CFLAGS = $(FLAGS)
ifdef YES
CFLAGS += -D BONUS_AVAILABLE
endif

$(NAME): sublibs $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINKS)  -o $(NAME)

bonus:
	make YES=1 $(NAME)

%.o: $(SRC_DIR)/%.c 
	$(CC) -Ilibft $(CFLAGS) -c $< -o $@  

all: $(NAME)

libft_build:
	if [ ! -f $(LIBFT_DIR)/libft.a ]; then \
		/Library/Developer/CommandLineTools/usr/bin/make -C $(LIBFT_DIR); \
	fi

ft_printf_build:
	if [ ! -f $(FT_PRINT_DIR)/libftprintf.a ]; then \
		/Library/Developer/CommandLineTools/usr/bin/make -C $(FT_PRINT_DIR); \
	fi

submodules:
	git submodule init
	git submodule update

sublibs: submodules libft_build ft_printf_build

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(FT_PRINT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(FT_PRINT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft_build submodules sublibs