# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qho <qho@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/07 19:11:31 by qho               #+#    #+#              #
#    Updated: 2017/05/07 19:41:43 by qho              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	proxy

# Flags and compiler
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

# Source and header files, and directory
INC		=	./inc/
FILES	=	proxy_01 proxy_02 proxy_03	\

SRC		=	$(addsuffix .c, $(FILES))

# Object directory and files
OBJ	=	$(addsuffix .o, $(FILES))

.PHONY: clean fclean re norm

all: $(NAME)

$(NAME): $(SRC)
	@echo "\033[32mCompiled libft\033[0m"
	@$(CC) -I$(INC) $(SRC) -o $(NAME)
	@echo "\033[32m$(NAME) compiled\033[0m"

norm:
	@norminette $(SRC) $(INC)

clean:
	@/bin/rm -rf $(OBJ)
	@echo "\033[31mCleaning object files\033[0m"

fclean: clean
	@/bin/rm -f $(NAME) $(EXE)
	@echo "\033[31mCleaning $(NAME)\033[0m"

re: fclean all