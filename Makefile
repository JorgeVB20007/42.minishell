# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/17 19:44:26 by emadriga          #+#    #+#              #
#    Updated: 2021/11/11 00:36:00 by jvacaris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program's name
NAME	= minishell

# compiling flags
FLAGS	= -Wall -Wextra -Werror $(SANITIZE)

# sanitize
# SANITIZE =
SANITIZE = -g3 -fsanitize=address

# readline doing readliney things
RLINE_INC	= -I/Users/$(USER)/.brew/opt/readline/include
RLINE_L		= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib

# Header files
INCLUDES_FILES =	errors.h		\
					constants.h		\
					minishell.h

# Source and object files
SRC_FILES	= 	minishell1.c				\
				modifsplit.c				\
				ms_parser.c					\
				var_expansor.c				\
				qm_error_detector.c			\
				interpreter.c				\
				exec_command.c				\
				heredoc.c					\
				builtins/env.c				\
				utils/lst_str_handler.c		\
				utils/lst_str_handler2.c	\
				utils/ft_strslashjoin.c		\
				utils/megafree.c			\
				utils/is_valid_var.c		\
				utils/qm_remover.c			\
				utils/ft_modstrcmp.c		\
				builtins/cd.c				\
				builtins/echo.c				\
				builtins/export.c			\
				builtins/pwd.c				\
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
$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(INCLUDES)
	@gcc $(FLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) $(RLINE_INC) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Compiling
$(NAME): $(OBJ)
	@echo "\033[0;33mCompiling... Wait a sec.\033[0;37m"
	@gcc $(OBJ) $(FLAGS) $(LNK) $(RLINE_L) -lm -o $(NAME)
	@echo "\033[0;32m$(NAME) generated!\033[0;37m"

mynorm:
	norminette $(SRC_DIR) $(INC_DIR) $(LIBFT_DIR)

bonus:	all

# clean rule
clean:
			@rm -Rf $(OBJ_DIR)
			@make -C $(LIBFT_DIR) clean
			@echo "[INFO] Objects removed!"

# fclean rule
fclean:		clean
			@rm -f $(NAME)
			@make -C $(LIBFT_DIR) fclean
			@echo "$(NAME) removed!"

# re rule
re:			fclean all bonus

# phony
.PHONY:		all bonus clean fclean re mynorm
