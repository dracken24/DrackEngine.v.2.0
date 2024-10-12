NAME = new_project

# Compilateur et options
CC = gcc
CFLAGS = -I./includes -I../../library/extern/raylib/src
RAYLIB_DIR = ../../library/extern/raylib/src

all: $(NAME)

re: clean all

clean:
	rm -f $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) main.c $(RAYLIB_DIR)/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11