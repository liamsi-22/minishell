NAME = minishell

SRC_FILES = main.c parsing/creat_nodes.c parsing/error_handling.c parsing/handle_quotes.c parsing/minishell_loop.c parsing/parser_1.c parsing/parser_2.c parsing/parser_original.c \
			parsing/token_reader.c parsing/token_reader2.c exec/builting_arr.c exec/exec1.c exec/exec2.c exec/exec3.c exec/exec4.c exec/exec5.c exec/exec6.c exec/exec7.c exec/exec8.c exec/mini_cd.c \
			exec/mini_echo.c exec/mini_env.c exec/mini_exit.c exec/mini_export.c exec/mini_pwd.c exec/mini_unset.c exec/utils_builtins.c \
			assistant_function/free_arr.c assistant_function/ft_arrdup.c assistant_function/ft_atoi.c assistant_function/ft_bzero.c \
			assistant_function/ft_itoa.c assistant_function/ft_putendl_fd.c assistant_function/ft_splite.c assistant_function/ft_strcmp.c \
			assistant_function/ft_strdup.c assistant_function/ft_strjoin.c \
			assistant_function/ft_strlcpy.c assistant_function/ft_strlen.c assistant_function/ft_strncmp.c assistant_function/ft_strncpy.c \
			assistant_function/ft_strtrim.c assistant_function/ft_substr.c \
			init_variables/initiat_tools.c

OBJ_FILES = $(SRC_FILES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINE_LIB = -l readline

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(READLINE_LIB) -o $@

clean :
	rm -f $(OBJ_FILES)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re

# NAME = minishell

# # Directories
# SRC_DIR = src
# BUILD_DIR = build
# INC_DIR = includes
# ASSISTANT_DIR = assistant_function
# PARSING_DIR = parsing
# BUILTINS_DIR = builtins

# # Source Files
# SRC_FILES = $(SRC_DIR)/main.c \
# 			$(PARSING_DIR)/creat_nodes.c $(SRC_DIR)/error_handling.c $(SRC_DIR)/handle_quotes.c $(SRC_DIR)/minishell_loop.c \
# 			$(SRC_DIR)/parser_1.c $(SRC_DIR)/parser_2.c $(SRC_DIR)/parser_original.c $(SRC_DIR)/token_reader.c \
# 			$(SRC_DIR)/token_reader2.c $(SRC_DIR)/builting_arr.c $(SRC_DIR)/exec1.c $(SRC_DIR)/exec2.c $(SRC_DIR)/exec3.c \
# 			$(SRC_DIR)/exec4.c $(SRC_DIR)/exec5.c $(SRC_DIR)/exec6.c $(SRC_DIR)/exec7.c $(SRC_DIR)/exec8.c \
# 			$(BUILTINS_DIR)/mini_cd.c $(BUILTINS_DIR)/mini_echo.c $(BUILTINS_DIR)/mini_env.c $(BUILTINS_DIR)/mini_exit.c \
# 			$(BUILTINS_DIR)/mini_export.c $(BUILTINS_DIR)/mini_pwd.c $(BUILTINS_DIR)/mini_unset.c $(BUILTINS_DIR)/utils_builtins.c \
# 			$(ASSISTANT_DIR)/free_arr.c $(ASSISTANT_DIR)/ft_arrdup.c $(ASSISTANT_DIR)/ft_atoi.c $(ASSISTANT_DIR)/ft_bzero.c \
# 			$(ASSISTANT_DIR)/ft_itoa.c $(ASSISTANT_DIR)/ft_putendl_fd.c $(ASSISTANT_DIR)/ft_splite.c $(ASSISTANT_DIR)/ft_strcmp.c \
# 			$(ASSISTANT_DIR)/ft_strdup.c $(ASSISTANT_DIR)/ft_strjoin.c $(ASSISTANT_DIR)/ft_strlcpy.c $(ASSISTANT_DIR)/ft_strlen.c \
# 			$(ASSISTANT_DIR)/ft_strncmp.c $(ASSISTANT_DIR)/ft_strncpy.c $(ASSISTANT_DIR)/ft_strtrim.c $(ASSISTANT_DIR)/ft_substr.c

# OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# # Compiler and Flags
# CC = cc
# CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -g
# READLINE_LIB = -lreadline

# # Create build directory if it doesn't exist
# $(BUILD_DIR):
# 	mkdir -p $(BUILD_DIR)

# # Compile object files
# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Link and create the executable
# $(NAME): $(OBJ_FILES)
# 	$(CC) $(OBJ_FILES) $(READLINE_LIB) -o $@

# # Clean object files
# clean:
# 	rm -f $(OBJ_FILES)

# # Clean everything
# fclean: clean
# 	rm -f $(NAME)

# # Rebuild
# re: fclean all

# # Phony targets
# .PHONY: all clean fclean re

# # Default target
# all: $(NAME)
