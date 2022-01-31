# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/17 19:44:26 by emadriga          #+#    #+#              #
#    Updated: 2022/01/31 21:30:32 by jvacaris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program's name
NAME	= minishell

# compiler
GCC		= clang

# compiling flags
FLAGS	= -Wall -Wextra -Werror $(SANITIZE) -pedantic

# sanitize
# SANITIZE =
SANITIZE = -g3 -fsanitize=address
# SANITIZE = -Ofast -fsanitize=address

# readline doing readliney things
RLINE_INC	= -I/Users/$(USER)/.brew/opt/readline/include
RLINE_L		= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib

# Header files
INCLUDES_FILES =	errors.h		\
					constants.h		\
					minishell.h

# Source and object files
SRC_FILES	= 	minishell.c							\
				expansions/var_expansor.c			\
				expansions/var_expansor2.c			\
				get_path.c							\
				builtins/env.c						\
				utils/lst_str_handler.c				\
				utils/lst_str_handler2.c			\
				utils/ft_strslashjoin.c				\
				utils/is_it_path.c					\
				utils/megafree.c					\
				utils/quote_mark_handler.c			\
				utils/lst_redir_handler.c			\
				utils/lst_process_handler.c			\
				utils/error_handler.c				\
				utils/error_handler2.c				\
				utils/error_handler3.c				\
				utils/ft_is_directory.c				\
				utils/token_handler.c				\
				utils/token_handler2.c				\
				utils/signal_handler.c				\
				forks/close_quotes.c				\
				forks/heredoc_handler.c				\
				processes/get_processes.c			\
				processes/process_redirections.c	\
				processes/run_processes.c			\
				builtins/builtins.c					\
				builtins/cd.c						\
				builtins/echo.c						\
				builtins/exit.c						\
				builtins/export.c					\
				builtins/pwd.c						\
				builtins/unset.c

OBJ_FILES	= $(SRC_FILES:.c=.o)

# Folders
SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/

# Paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INCLUDES = $(addprefix $(INC_DIR), $(INCLUDES_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

# Libft linkers
LNK  = -L $(LIBFT_DIR) -lft $(SANITIZE)

# all rule
all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)utils/
	@mkdir -p $(OBJ_DIR)builtins/
	@mkdir -p $(OBJ_DIR)forks/
	@mkdir -p $(OBJ_DIR)processes/
	@mkdir -p $(OBJ_DIR)expansions/
$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(INCLUDES)
	@$(GCC) $(FLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) $(RLINE_INC) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Compiling
$(NAME): $(OBJ)
	@echo "\033[0;33mCompiling... Wait a sec.\033[0;31m"
	@$(GCC) $(OBJ) $(FLAGS) $(LNK) $(RLINE_L) -lm -o $(NAME)
	@echo "\033[0;32m$(NAME) generated!\033[0;37m"

mynorm:
	norminette $(SRC_DIR) $(INC_DIR) $(LIBFT_DIR)

bonus:	all

# clean rule
clean:
			@rm -Rf $(OBJ_DIR)
			@make -C $(LIBFT_DIR) clean
			@echo "\033[1;34m[INFO]\033[0m Objects removed!"

# fclean rule
fclean:		clean
			@rm -f $(NAME)
			@make -C $(LIBFT_DIR) fclean
			@echo "$(NAME) removed!"

# re rule
re:			fclean all bonus

# phony
.PHONY:		all clean fclean re mynorm
