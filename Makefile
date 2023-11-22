# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 14:07:23 by pbalbino          #+#    #+#              #
#    Updated: 2023/11/22 16:43:13 by pbalbino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CC		=	cc
CFLAGS	=	-pthread -Wall -Werror -Wextra -g3

SRC_PATH = 	sources/
OBJ_PATH = objects/

SRC	=		actions.c \
			actions2.c \
			init.c \
			input_validation.c \
			main.c \
			simulation.c \
			utils.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INC		= -I ./includes/

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean




