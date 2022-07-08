# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 13:19:06 by mbarutel          #+#    #+#              #
#    Updated: 2022/07/08 13:10:07 by mbarutel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables

NAME		= libftprintf.a
LIBFT		= libft
INCLUDE		= incs
SRC_DIR		= srcs/
CC			= gcc
CFLAGS		= -g -Wall -Werror -Wextra -I
RM			= rm -f
AR			= ar rcs

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# Sources

SRC_FILES    =    ft_arg_filter
SRC_FILES    +=    ft_char_convert
SRC_FILES    +=    ft_printers
SRC_FILES    +=    ft_diouxf_convert
SRC_FILES    +=    ft_colouring
SRC_FILES    +=    ft_printf
SRC_FILES    +=    ft_str_convert
SRC_FILES    +=    ft_utils
SRC_FILES    +=    ft_bonus_func
SRC_FILES    +=    ft_printer_utils

SRC         =     $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ         =     $(addsuffix .o, $(SRC_FILES))

###

all:	$(NAME)

$(NAME): $(SRC)
	@make -C $(LIBFT)
	@cp $(LIBFT)/libft.a .
	@mv libft.a $(NAME)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $(SRC)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(GREEN)ft_printf compiled!$(DEF_COLOR)"

clean:
	@$(RM) -rf $(OBJ)
	@make clean -C $(LIBFT)
	@echo "$(BLUE)ft_printf object files cleaned!$(DEF_COLOR)"

fclean:	clean
	@$(RM) -f $(NAME)
	@$(RM) -f $(LIBFT)/libft.a
	@echo "$(CYAN)ft_printf executable files cleaned!$(DEF_COLOR)"
	@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re:	fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything for ft_printf!$(DEF_COLOR)"

libft:
	@make re -C $(LIBFT)

.PHONY:	all clean fclean re