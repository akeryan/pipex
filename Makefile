# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/14 19:39:20 by akeryan           #+#    #+#              #
#    Updated: 2023/12/21 16:06:27 by akeryan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
FLAGS		= -Wall -Wextra -Werror
LINKS		= -Ilibft -Llibft -lft

SRC_DIR		= src
LIBFT_DIR	= libft
MANDATORY	= pipex.c path.c error.c parsing.c init.c clean.c utils.c main.c
CC			= cc


OBJ = $(patsubst %.c, %.o, $(MANDATORY))

$(NAME): sublibs $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LINKS)  -o $(NAME)

%.o: $(SRC_DIR)/%.c 
	$(CC) -Ilibft $(FLAGS) -c $< -o $@  

all: $(NAME)

libft_build:
	if [ ! -f $(LIBFT_DIR)/libft.a ]; then \
		/Library/Developer/CommandLineTools/usr/bin/make -C $(LIBFT_DIR); \
	fi

submodules:
	git submodule init
	git submodule update

sublibs: submodules libft_build

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft_build submodules sublibs