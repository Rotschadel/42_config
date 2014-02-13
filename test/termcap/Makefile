#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/25 12:11:15 by mdelage           #+#    #+#              #
#    Updated: 2014/02/12 17:00:07 by mdelage          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CPATH = srcs
HPATH = includes
OPATH = obj
LIBPATH = ~/libft

NAME = a.out

CC = /usr/bin/gcc
MKDIR = /bin/mkdir
RM = /bin/rm
CFLAGS = -Wall -Wextra -Werror -I $(HPATH) -I $(LIBPATH)/includes/
LDFLAGS = -L $(LIBPATH) -lft -ltermcap

SRC = ft_minishell2.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Building $(NAME)"
	@$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	@echo "Creating file $@"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Deletion of building files"
	@$(RM) -f $(OBJ)

fclean: clean
	@echo "Deletion of $(NAME)"
	@$(RM) -f $(NAME)

re: fclean all

$(OPATH):
	@echo "Creation of building directory"
	@$(MKDIR) $(OPATH)
