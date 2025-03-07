# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: damendez <damendez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/07 15:22:30 by damendez          #+#    #+#              #
#    Updated: 2025/03/07 17:16:22 by damendez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= PmergeMe

SRC_FILES	= main.cpp PmergeMe.cpp

HEADER		= PmergeMe.hpp

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