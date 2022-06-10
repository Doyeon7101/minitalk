# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpark <dpark@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 21:24:32 by dpark             #+#    #+#              #
#    Updated: 2022/06/10 21:24:38 by dpark            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

S_SERVER= server.c
O_SERVER = $(S_SERVER:.c=.o)

S_CLIENT = client.c
O_CLIENT = $(S_CLIENT:.c=.o)

S_UTILS = tools.c ft_printf.c
O_UTILS = $(S_UTILS:.c=.o)


all: $(SERVER) $(CLIENT)

$(SERVER): $(O_SERVER) $(O_UTILS)
			$(CC) $(CFLAGS) $^ -o $@

$(CLIENT): $(O_CLIENT) $(O_UTILS)
			$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(O_SERVER) $(O_CLIENT) $(O_UTILS)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re