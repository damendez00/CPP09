# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: damendez <damendez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 14:54:13 by damendez          #+#    #+#              #
#    Updated: 2024/12/19 17:55:35 by damendez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= btc

SRC_FILES	= main.cpp

HEADER		= BitcoinExchange.hpp

OBJ_DIR		= obj/
OBJ_FILES	= $(SRC_FILES:.cpp=.o)
OBJS		= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

DEP_FILES	= $(SRC_FILES:.cpp=.d)
DEPS		= $(addprefix $(OBJ_DIR), $(DEP_FILES))

CC			= c++
CFLAGS		= -std=c++98 -Wall -Wextra -Werror -MMD -g
RM			= rm -rf
INCLUDE		= -I ./

all: $(NAME)

$(NAME): $(HEADER) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: %.cpp $(HEADER) Makefile | $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS) $(DEPS)

fclean: clean
		$(RM) -r $(OBJ_DIR)
		$(RM) $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re