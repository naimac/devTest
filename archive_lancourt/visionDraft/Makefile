# MULTI COMMENTAIRE EN MAKEFILE \
test test

.PHONY: clean fclean clean-all re all

#directories: \
	@mkdir -p ./obj/

## DIRECTORIES
SRC_DIR		:= ./src/
INC_DIR		:= ./include/
OBJ_DIR		:= ./obj/
//LIBPATH		:= ../apishm/lib/

## COMPILER
CC		:= g++
CFLAGS		:= -std=c++11 -I$(INC_DIR) -Wall -Wextra -Werror -g -O0 -pthread
# CPPFLAGS 	:= -I$(LTST_HDR)
# LDFLAGS	:= -L$(LTST_DIR)
# LDLIBS	:= -lTest

## PROJECT FILES
NAME			:= exeVisionDraft
#SRCS			:= $(wildcard $(SRC_DIR)*.c) # marche mal ici
SRCS			:= main.cpp
OBJS     		:= $(patsubst %.cpp, $(OBJ_DIR)%.o, $(SRCS))
#OBJS			:= $(SRCS:.c=.o) # marche pas ici
#OBJS			:= $(SRCS:.c=$(OBJ_DIR).o) # marche pas ici

## RULES
all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@echo "creating OBJ_DIR"
	@mkdir -p $@

$(NAME): $(OBJS)
	@echo "creation de l'executable"
	$(CC) $(CFLAGS) -o $@ $^

# construire un .o à partir d'un .c
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@echo "creation des objets .o"
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBPATH)libshm.a:
	@($MAKE) -C $(LIBPATH)

clean:
	rm -fR $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

clean-all: fclean
	$(MAKE) fclean -C $(LTST_DIR)

re: fclean all
