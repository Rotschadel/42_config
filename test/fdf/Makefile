#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/21 16:25:16 by mdelage           #+#    #+#              #
#    Updated: 2013/12/21 19:44:40 by mdelage          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = caca

SRC = test.c

OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) -L /usr/X11/lib/ -lmlx -lXext -lX11 $^

%.o: %.c
	gcc -c $^ -o $@

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all
