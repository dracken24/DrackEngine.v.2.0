# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 11:43:06 by nadesjar          #+#    #+#              #
#    Updated: 2022/12/14 03:26:32 by nadesjar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_OBJS		= ./objs/

FILES 		= logger.c

OBJS		= $(patsubst %.c, $(P_OBJS)%.o, $(FILES))
			
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra

NAME		= libdrackengine.a

all: $(NAME)

$(NAME): msg_in $(OBJS) msg_out
	@ar -rcs $(NAME) $(OBJS)

$(P_OBJS)%.o:	%.c
	@mkdir -p $(P_OBJS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$G■"

msg_in:
	@echo $L"Compiling DrackEngine Library..."$W

msg_out:
	@echo '\n'$G"DrackEngine Library compiled successfully"$W

clean:
	@rm -fr ./objs

fclean: clean
	@rm -f $(NAME)

re:	fclean all

L	= $(shell tput -Txterm setaf 5)
R	= $(shell tput -Txterm setaf 1)
G	= $(shell tput -Txterm setaf 2)
C	= $(shell tput -Txterm setaf 6)
W	= $(shell tput -Txterm setaf 7)

.PHONY: all msg_in msg_out clean fclean re
