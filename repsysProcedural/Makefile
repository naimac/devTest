.PHONY: all clean fclean re

SRC_PATH = ./src/
LIB_PATH = ./system/bp/lib/
INC_PATH = ./system/bp/external/
CC = gcc
CFLAGS = -g -O0 -m32
NAME = reporter_message

SRC = \
		$(SRC_PATH)main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@echo "Compilation$@"
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_PATH) -I$(LIB_PATH) 

$(LIB_PATH)libft.a:
	@$(MAKE) -C $(LIB_PATH)

$(NAME): $(OBJ)
	@echo "Linkage"
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIB_PATH) -lBPApi -o $(NAME) 
	@echo "\033[1;32m\nDone !\033[1;0m"

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
