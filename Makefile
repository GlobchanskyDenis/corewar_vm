# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/13 12:16:02 by bsabre-c          #+#    #+#              #
#    Updated: 2019/11/23 16:40:18 by jmaynard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= corewar
FLAGS		= -Wall -Wextra -Werror -g

# directories
DIR_O		=	objects

# files
SRC			=	vm_main.c						vm_free_exit.c				\
				vm_reader.c						vm_parse_flags_1.c			\
				vm_parse_flags_2.c				vm_extract.c				\
				vm_carriage_1.c					vm_carriage_2.c				\
				vm_initialize_all.c				vm_initialize_game.c		\
				vm_temp.c						vm_initialize_commands.c

OBJ			=	$(addprefix $(DIR_O)/,$(SRC:.c=.o))

#MLX			= 	-L./mlx -lmlx -framework OpenGL -framework AppKit

# libraries
L_FT_D 		= 	./libft
L_FT_L 		= 	$(L_FT_D)/libft.a

.PHONY: all clean fclean re proj

$(NAME) : $(OBJ)
			@make -sC $(L_FT_D)
			@echo "Compiling corewar"
			@gcc $(FLAGS) $(OBJ) $(L_FT_L) -o $(NAME)
			@echo "File $(NAME) was created succesfully"

$(DIR_O)/%.o: %.c vm.h op.h
			@mkdir -p $(DIR_O)
			@gcc $(FLAGS) -o $@ -c $<

clean :
			@echo "Start cleaning"
			@make clean -sC $(L_FT_D)
			@rm -rf .DS_Store
			@rm -rf $(L_FT_D)/.DS_Store
			@rm -rf $(DIR_O)
			@echo "Cleaning finished"

fclean : clean
			@rm -rf $(L_FT_L)
			@rm -rf $(NAME)
			@rm -rf $(NAME).dSYM

all : 		$(NAME)

re: fclean all
