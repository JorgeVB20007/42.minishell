# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/17 19:44:26 by emadriga          #+#    #+#              #
#    Updated: 2021/10/31 19:27:10 by emadriga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program's name
NAME	= minishell

# compiling flags
FLAGS	= -Wall -Wextra -Werror

# readline doing readliney things
RLINE_INC	= -I/Users/$(USER)/.brew/opt/readline/include
RLINE_L		= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib

# Header files
INCLUDES_FILES =	errors.h	\
					minishell.h

# Source and object files
SRC_FILES	= 	minishell1.c		\
				modifsplit.c		\
				var_expansor.c		\
				interpreter.c		\
				echo.c				\
				envutils.c			\
				pwd.c

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

# Libft and Minilibx linkers
LNK  = -L $(LIBFT_DIR) -lft

# all rule
all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(INCLUDES)
	@gcc $(FLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) $(RLINE_INC) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Compiling
$(NAME): $(OBJ)
	@echo "\033[0;33mCompiling... Wait a sec.\033[0;37m"
	@gcc $(OBJ) $(FLAGS) $(LNK) $(RLINE_L) -lm -o $(NAME)
	@echo "\033[0;32m$(NAME) generated!\033[0;37m".

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