SERVER = server
CLIENT = client

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

SRC_S = server.c
SRC_C = client.c
SRC_U = tools.c ft_printf.c

OBJ_S = $(SRC_S:.c=.o)
OBJ_C = $(SRC_C:.c=.o)
OBJ_U = $(SRC_U:.c=.o)


all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_S) $(OBJ_U)
			$(CC) $(CFLAGS) $^ -o $@

$(CLIENT): $(OBJ_C) $(OBJ_U)
			$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(OBJ_S) $(OBJ_C) $(OBJ_U)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re