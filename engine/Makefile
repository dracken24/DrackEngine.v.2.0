# Nom des exécutables et bibliothèques
NAME = DrackEngine
CORE_LIB = libdrackcore.a

# Compilateurs et options
CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -I./includes -I../library/extern/raylib/src
CFLAGS += -I./engine/includes -I./engine/srcs/utility
CFLAGS += -I./library/libft
CFLAGS += -I./library/drackengine_lib
CXXFLAGS = $(CFLAGS) -std=c++17
LINKFLAGS = -lGL -lm -lpthread -ldl -lrt -lX11 -lcjson

# Dossiers
CORE_DIR = core
WRAPPER_DIR = wrapper
INC_DIR = includes
OBJ_DIR = obj
LIBFT_DIR = ../library/libft
RAYLIB_DIR = ../library/extern/raylib/src
LIBDRACKENGINE_DIR = ../library/drackengine_lib

# Sources
CORE_SRCS = $(shell find $(CORE_DIR) -name '*.c')
WRAPPER_SRCS = $(shell find $(WRAPPER_DIR) -name '*.cpp')

# Objets
CORE_OBJS = $(CORE_SRCS:$(CORE_DIR)/%.c=$(OBJ_DIR)/core/%.o)
WRAPPER_OBJS = $(WRAPPER_SRCS:$(WRAPPER_DIR)/%.cpp=$(OBJ_DIR)/wrapper/%.o)

# Bibliothèques externes
LIBFT = $(LIBFT_DIR)/libft.a
RAYLIB = $(RAYLIB_DIR)/libraylib.a
LIBDRACKENGINE = $(LIBDRACKENGINE_DIR)/libdrackengine.a

# ... (garder vos définitions de couleurs existantes) ...

# Règle par défaut
all: $(NAME)

# Création de l'exécutable final (C++)
$(NAME): $(CORE_LIB) $(WRAPPER_OBJS) $(LIBFT) $(RAYLIB) $(LIBDRACKENGINE)
	@echo "$(BLUE)╔══════════════════════════════════════╗$(RESET)"
	@echo "$(BLUE)║     Création de l'exécutable...      ║$(RESET)"
	@echo "$(BLUE)╚══════════════════════════════════════╝$(RESET)"
	@$(CXX) $(CXXFLAGS) $(WRAPPER_OBJS) -L. -ldrackcore -L$(LIBFT_DIR) -lft $(RAYLIB) $(LIBDRACKENGINE) $(LINKFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ Exécutable $(NAME) créé avec succès !$(RESET)"

# Compilation des fichiers sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compilation de $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Création de la bibliothèque core (C)
$(CORE_LIB): $(CORE_OBJS)
	@echo "$(BLUE)╔══════════════════════════════════════╗$(RESET)"
	@echo "$(BLUE)║  Création de la bibliothèque core... ║$(RESET)"
	@echo "$(BLUE)╚══════════════════════════════════════╝$(RESET)"
	@ar rcs $(CORE_LIB) $(CORE_OBJS)
	@echo "$(GREEN)✓ Bibliothèque core créée avec succès !$(RESET)"

# Compilation des fichiers sources C++
$(OBJ_DIR)/wrapper/%.o: $(WRAPPER_DIR)/%.cpp
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compilation de $<...$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation de la libft
$(LIBFT):
	@echo "$(BLUE)╔════════════════════════════════════════╗$(RESET)"
	@echo "$(BLUE)║       Compilation de la libft...       ║$(RESET)"
	@echo "$(BLUE)╚════════════════════════════════════════╝$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

# Compilation de Raylib
$(RAYLIB):
	@echo "$(BLUE)╔════════════════════════════════════════╗$(RESET)"
	@echo "$(BLUE)║       Compilation de Raylib...         ║$(RESET)"
	@echo "$(BLUE)╚════════════════════════════════════════╝$(RESET)"
	@$(MAKE) -C $(RAYLIB_DIR) PLATFORM=PLATFORM_DESKTOP

# Compilation de la libdrackengine
$(LIBDRACKENGINE):
	@echo "$(BLUE)╔════════════════════════════════════════╗$(RESET)"
	@echo "$(BLUE)║  Compilation de la libdrackengine...   ║$(RESET)"
	@echo "$(BLUE)╚════════════════════════════════════════╝$(RESET)"
	@$(MAKE) -C $(LIBDRACKENGINE_DIR)

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

re: fclean all

.PHONY: all clean fclean re

# # Nom de l'exécutable
# NAME = DrackEngine

# # Compilateur et options
# CC = gcc
# # CFLAGS = -Wall -Wextra -Werror -I./includes -I../library/extern/raylib/src
# CFLAGS = -I./includes -I../library/extern/raylib/src
# CFLAGS += -I./engine/includes -I./engine/srcs/utility
# CFLAGS += -I./library/libft
# CFLAGS += -I./library/drackengine_lib
# LINKFLAGS = -lGL -lm -lpthread -ldl -lrt -lX11 -lcjson

# # Dossiers
# SRC_DIR = srcs
# INC_DIR = includes
# OBJ_DIR = obj
# LIBFT_DIR = ../library/libft
# RAYLIB_DIR = ../library/extern/raylib/src
# LIBDRACKENGINE_DIR = ../library/drackengine_lib
# # Sources et objets
# SRCS = $(shell find $(SRC_DIR) -name '*.c')
# OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# # Libft et Raylib
# LIBFT = $(LIBFT_DIR)/libft.a
# RAYLIB = $(RAYLIB_DIR)/libraylib.a
# LIBDRACKENGINE = $(LIBDRACKENGINE_DIR)/libdrackengine.a

# # Couleurs
# RED = \033[0;31m
# GREEN = \033[0;32m
# YELLOW = \033[0;33m
# BLUE = \033[0;34m
# RESET = \033[0m

# # Règle par défaut
# all: $(NAME)

# # Création de l'exécutable
# $(NAME): $(OBJS) $(LIBFT) $(RAYLIB) $(LIBDRACKENGINE)
# 	@echo "$(BLUE)╔══════════════════════════════════════╗$(RESET)"
# 	@echo "$(BLUE)║     Création de l'exécutable...      ║$(RESET)"
# 	@echo "$(BLUE)╚══════════════════════════════════════╝$(RESET)"
# 	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(RAYLIB) $(LIBDRACKENGINE) $(LINKFLAGS) -o $(NAME)
# 	@echo "$(GREEN)✓ Exécutable $(NAME) créé avec succès !$(RESET)"

# # Compilation des fichiers sources
# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	@mkdir -p $(@D)
# 	@echo "$(YELLOW)Compilation de $<...$(RESET)"
# 	@$(CC) $(CFLAGS) -c $< -o $@

# # Compilation de la libft
# $(LIBFT):
# 	@echo "$(BLUE)╔════════════════════════════════════════╗$(RESET)"
# 	@echo "$(BLUE)║       Compilation de la libft...       ║$(RESET)"
# 	@echo "$(BLUE)╚════════════════════════════════════════╝$(RESET)"
# 	@$(MAKE) -C $(LIBFT_DIR)

# # Compilation de Raylib
# $(RAYLIB):
# 	@echo "$(BLUE)╔════════════════════════════════════════╗$(RESET)"
# 	@echo "$(BLUE)║       Compilation de Raylib...         ║$(RESET)"
# 	@echo "$(BLUE)╚════════════════════════════════════════╝$(RESET)"
# 	@$(MAKE) -C $(RAYLIB_DIR) PLATFORM=PLATFORM_DESKTOP

# # Compilation de la libdrackengine
# $(LIBDRACKENGINE):
# 	@echo "$(BLUE)╔════════════════════════════════════════╗$(RESET)"
# 	@echo "$(BLUE)║  Compilation de la libdrackengine...   ║$(RESET)"
# 	@echo "$(BLUE)╚════════════════════════════════════════╝$(RESET)"
# 	@$(MAKE) -C $(LIBDRACKENGINE_DIR)



# # Nettoyage
# clean:
# 	@echo "$(RED)Nettoyage des fichiers objets...$(RESET)"
# 	@rm -rf $(OBJ_DIR)
# 	@echo "$(GREEN)✓ Nettoyage terminé !$(RESET)"

# fclean: clean
# 	@echo "$(RED)Suppression de l'exécutable $(NAME)...$(RESET)"
# 	@rm -f $(NAME)
# 	@$(MAKE) -C $(LIBFT_DIR) fclean
# 	@$(MAKE) -C $(RAYLIB_DIR) clean
# 	@$(MAKE) -C $(LIBDRACKENGINE_DIR) fclean
# 	@echo "$(GREEN)✓ Nettoyage complet terminé !$(RESET)"

# # Recompilation
# re: clean all

# relib: fclean all

# .PHONY: all clean fclean re relib
