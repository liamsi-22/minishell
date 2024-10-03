NAME = minishell
P_DIR = parsing
A_DIR = assistant_function
E_DIR = exec

SRC_FILES = main.c $(P_DIR)/creat_nodes.c $(P_DIR)/error_handling.c $(P_DIR)/handle_quotes.c $(P_DIR)/minishell_loop.c \
			$(P_DIR)/parser_1.c $(P_DIR)/parser_2.c $(P_DIR)/parser_original.c $(P_DIR)/token_reader.c $(P_DIR)/token_reader2.c \
			$(E_DIR)/builting_arr.c $(E_DIR)/exec1.c $(E_DIR)/exec2.c $(E_DIR)/exec3.c $(E_DIR)/exec4.c $(E_DIR)/exec5.c $(E_DIR)/exec6.c \
			$(E_DIR)/exec7.c $(E_DIR)/exec8.c $(E_DIR)/mini_cd.c $(E_DIR)/mini_echo.c $(E_DIR)/mini_env.c $(E_DIR)/mini_exit.c \
			$(E_DIR)/mini_export.c $(E_DIR)/mini_pwd.c $(E_DIR)/mini_unset.c $(E_DIR)/utils_builtins.c $(A_DIR)/free_arr.c \
			$(A_DIR)/ft_arrdup.c $(A_DIR)/ft_atoi.c $(A_DIR)/ft_bzero.c $(A_DIR)/ft_itoa.c $(A_DIR)/ft_putendl_fd.c $(A_DIR)/ft_splite.c \
			$(A_DIR)/ft_strcmp.c $(A_DIR)/ft_strdup.c $(A_DIR)/ft_strjoin.c $(A_DIR)/ft_strlcpy.c $(A_DIR)/ft_strlen.c $(A_DIR)/ft_strncmp.c \
			$(A_DIR)/ft_strncpy.c $(A_DIR)/ft_strtrim.c $(A_DIR)/ft_substr.c init_variables/initiat_tools.c

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