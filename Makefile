# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qho <qho@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/07 19:11:31 by qho               #+#    #+#              #
#    Updated: 2017/05/07 22:43:19 by qho              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_NAME	=	proxy
S_NAME	=	server
C_NAME	=	client

# Flags and compiler
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

# Source and header files, and directory
P_INC		=	./inc/proxy
C_INC		=	./inc/client
PROXY_FILES	=	proxy_01 proxy_02 proxy_03
S_FILES	=	server
C_FILES =	client_01 client_02


PROXY_SRC		=	$(addsuffix .c, $(PROXY_FILES))
S_SRC	=	$(addsuffix .c, $(S_FILES))
C_SRC	=	$(addsuffix .c, $(C_FILES))

# Object directory and files
PROXY_OBJ	=	$(addsuffix .o, $(PROXY_FILES))
S_OBJ	=	$(addsuffix .o, $(S_FILES))
C_OBJ	=	$(addsuffix .o, $(C_FILES))

.PHONY: clean fclean re norm

all: $(P_NAME) $(S_NAME) $(C_NAME)

$(P_NAME): $(PROXY_SRC)
	@$(CC) -I$(P_INC) $(PROXY_SRC) -o $(P_NAME) -lpthread
	@echo "\033[32m$(P_NAME) compiled\033[0m"

$(S_NAME): $(S_SRC)
	@$(CC) $(S_SRC) -o $(S_NAME)
	@echo "\033[32m$(S_NAME) compiled\033[0m"

$(C_NAME): $(C_SRC)
	@$(CC) -I$(C_INC) $(C_SRC) -o $(C_NAME)
	@echo "\033[32m$(C_NAME) compiled\033[0m"

norm:
	@norminette $(PROXY_SRC) $(S_SRC) $(C_SRC) $(INC)

clean:
	@/bin/rm -rf $(PROXY_OBJ) $(C_OBJ) $(S_OBJ)
	@echo "\033[31mCleaning object files\033[0m"

fclean: clean
	@/bin/rm -f $(P_NAME) $(S_NAME) $(C_NAME) $(EXE)
	@echo "\033[31mCleaning $(NAME)\033[0m"

re: fclean all