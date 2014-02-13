#*******************************************************************************#
#                                                                               #
#                                                          :::      ::::::::    #
#    Makefile                                            :+:      :+:    :+:    #
#                                                      +:+ +:+         +:+      #
#    by: mdelage <mdelage@student.42.fr>             +#+  +:+       +#+         #
#                                                  +#+#+#+#+#+   +#+            #
#    Created: 2014/01/04 13:41:53 by mdelage            #+#    #+#              #
#    Updated: 2014/01/04 18:06:57 by mdelage           ###   ########.fr        #
#                                                                               #
#*******************************************************************************#

NAME = ft_select

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_select.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -l termcap $^ -o $@

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all
