NAME = file_open

# Compilateur et options
CC = gcc
CFLAGS = -I./includes -I../../library/extern/raylib/src
RAYLIB_DIR = ../../library/extern/raylib/src
# UTILITY_DIR = ../windows_utility.c
DRACKENGINE_DIR = ../../library/drackengine_lib

all: $(NAME)

re: clean all

clean:
	rm -f $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) main.c $(RAYLIB_DIR)/libraylib.a $(DRACKENGINE_DIR)/libdrackengine.a -lGL -lm -lpthread -ldl -lrt -lX11 -o $(NAME)
