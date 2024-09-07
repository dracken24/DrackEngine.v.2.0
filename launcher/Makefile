# Nom de l'exécutable
NAME = DrackLauncher

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./includes -I../library/extern/raylib/src
LINKFLAGS = -lGL -lm -lpthread -ldl -lrt -lX11

# Dossiers
SRC_DIR = srcs
INC_DIR = includes
OBJ_DIR = obj
LIBFT_DIR = ../library/libft
RAYLIB_DIR = ../library/extern/raylib/src

# Sources et objets
SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libft et Raylib
LIBFT = $(LIBFT_DIR)/libft.a
RAYLIB = $(RAYLIB_DIR)/libraylib.a

# Couleurs
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

# Règle par défaut
all: $(NAME)

# Création de l'exécutable
$(NAME): $(OBJS) $(LIBFT) $(RAYLIB)
	@echo "$(BLUE)╔══════════════════════════════════════╗$(RESET)"
	@echo "$(BLUE)║     Création de l'exécutable...      ║$(RESET)"
	@echo "$(BLUE)╚══════════════════════════════════════╝$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(RAYLIB) $(LINKFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ Exécutable $(NAME) créé avec succès !$(RESET)"

# Compilation des fichiers sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compilation de $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Compilation de la libft
$(LIBFT):
	@echo "$(BLUE)╔══════════════════════════════════════╗$(RESET)"
	@echo "$(BLUE)║      Compilation de la libft...      ║$(RESET)"
	@echo "$(BLUE)╚══════════════════════════════════════╝$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

# Compilation de Raylib
$(RAYLIB):
	@echo "$(BLUE)╔══════════════════════════════════════╗$(RESET)"
	@echo "$(BLUE)║     Compilation de Raylib...         ║$(RESET)"
	@echo "$(BLUE)╚══════════════════════════════════════╝$(RESET)"
	@$(MAKE) -C $(RAYLIB_DIR) PLATFORM=PLATFORM_DESKTOP



# Nettoyage
clean:
	@echo "$(RED)Nettoyage des fichiers objets...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)✓ Nettoyage terminé !$(RESET)"

fclean: clean
	@echo "$(RED)Suppression de l'exécutable $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(RAYLIB_DIR) clean
	@echo "$(GREEN)✓ Nettoyage complet terminé !$(RESET)"

# Recompilation
re: clean all

relib: fclean all

.PHONY: all clean fclean re relib
