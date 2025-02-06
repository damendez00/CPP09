# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: damendez <damendez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/28 14:57:42 by damendez          #+#    #+#              #
#    Updated: 2025/02/06 16:04:28 by damendez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= RPN

SRC_FILES	= main.cpp RPN.cpp

HEADER		= RPN.hpp

OBJ_DIR		= obj/
OBJ_FILES	= $(SRC_FILES:.cpp=.o)
OBJS		= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

DEP_FILES	= $(SRC_FILES:.cpp=.d)
DEPS		= $(addprefix $(OBJ_DIR), $(DEP_FILES))

CC			= c++
CFLAGS		= -std=c++98 -Wall -Wextra -Werror -MMD -fsanitize=address -g
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