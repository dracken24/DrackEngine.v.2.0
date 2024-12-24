# $(info CORE_SRCS = $(CORE_SRCS))
# $(info CORE_OBJS = $(CORE_OBJS))

# Nom des exécutables et bibliothèques
NAME = DrackEngine
CORE_LIB = libdrackcore.a

# Compilateurs et options
CC = gcc
CXX = g++
# CXX = g++ -v
CFLAGS = -I./includes -I../library/extern/raylib/src
CFLAGS += -I./engine/includes -I./engine/srcs/utility
CFLAGS += -I./library/libft
CFLAGS += -I./library/drackengine_lib
CXXFLAGS = $(CFLAGS) -std=c++17 -I/usr/include/c++/VERSION
LINKFLAGS = -lGL -lm -lpthread -ldl -lrt -lX11 -lcjson

# Dossiers
CORE_DIR = core
WRAPPER_DIR = wrapper
INC_DIR = includes
OBJ_DIR = obj
LIBFT_DIR = ../library/libft
RAYLIB_DIR = ../library/extern/raylib/src
LIBDRACKENGINE_DIR = ../library/drackengine_lib

# Sources avec chemins complets
CORE_SRCS = $(shell find $(CORE_DIR) -name '*.c')
WRAPPER_SRCS = $(shell find $(WRAPPER_DIR) -name '*.cpp')

# Objets - Modification de la transformation des chemins
CORE_OBJS = $(CORE_SRCS:%.c=$(OBJ_DIR)/%.o)
WRAPPER_OBJS = $(WRAPPER_SRCS:%.cpp=$(OBJ_DIR)/%.o)

# Bibliothèques externes
LIBFT = $(LIBFT_DIR)/libft.a
RAYLIB = $(RAYLIB_DIR)/libraylib.a
LIBDRACKENGINE = $(LIBDRACKENGINE_DIR)/libdrackengine.a

# ... (garder vos définitions de couleurs existantes) ...

# Règle par défaut
all: $(NAME)

# Création de l'exécutable final (C++)
$(NAME): $(CORE_LIB) $(WRAPPER_OBJS) $(LIBFT) $(RAYLIB) $(LIBDRACKENGINE)
	@echo "$(CYAN)╔══════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║     Création de l'exécutable...      ║$(RESET)"
	@echo "$(CYAN)╚══════════════════════════════════════╝$(RESET)"
	@$(CXX) $(CXXFLAGS) $(WRAPPER_OBJS) -L. -ldrackcore -L$(LIBFT_DIR) -lft $(RAYLIB) $(LIBDRACKENGINE) $(LINKFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ Exécutable $(NAME) créé avec succès !$(RESET)"

# Compilation des fichiers sources
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "$(MAGENTA)Compilation de $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Compilation des fichiers sources C++
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@echo "$(MAGENTA)Compilation de $<...$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Création de la bibliothèque core (C)
$(CORE_LIB): $(CORE_OBJS)
	@echo "$(CYAN)╔══════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║  Création de la library core in c... ║$(RESET)"
	@echo "$(CYAN)╚══════════════════════════════════════╝$(RESET)"
	@ar rcs $(CORE_LIB) $(CORE_OBJS)
	@echo "$(GREEN)✓ Bibliothèque core créée avec succès !$(RESET)"

# Compilation de la libft
$(LIBFT):
	@echo "$(CYAN)╔════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║       Compilation de la libft...       ║$(RESET)"
	@echo "$(CYAN)╚════════════════════════════════════════╝$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

# Compilation de Raylib
$(RAYLIB):
	@echo "$(CYAN)╔════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║       Compilation de Raylib...         ║$(RESET)"
	@echo "$(CYAN)╚════════════════════════════════════════╝$(RESET)"
	@$(MAKE) -C $(RAYLIB_DIR) PLATFORM=PLATFORM_DESKTOP

# Compilation de la libdrackengine
$(LIBDRACKENGINE):
	@echo "$(CYAN)╔════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║  Compilation de la libdrackengine...   ║$(RESET)"
	@echo "$(CYAN)╚════════════════════════════════════════╝$(RESET)"
	@$(MAKE) -C $(LIBDRACKENGINE_DIR)

# Colors

BLUE = \033[0;34m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

# Nettoyage
clean:
	@echo "$(RED)Nettoyage des fichiers objets...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)✓ Nettoyage terminé !$(RESET)"

fclean: clean
	@echo "$(RED)Suppression de l'exécutable et des bibliothèques...$(RESET)"
	@rm -f $(NAME) $(CORE_LIB)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(RAYLIB_DIR) clean
	@$(MAKE) -C $(LIBDRACKENGINE_DIR) fclean
	@echo "$(GREEN)✓ Nettoyage complet terminé !$(RESET)"

re: clean all

.PHONY: all clean fclean re
