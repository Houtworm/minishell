# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: djonker <djonker@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/19 15:20:20 by djonker       #+#    #+#                  #
#    Updated: 2023/08/24 15:16:57 by yitoh         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=minishell
CC		=gcc
CFLAGS	=-Wall -Werror -Wextra# -g -fsanitize=address
RM		=rm -f
SRC		=src/main.c\
		 src/init.c\
		 src/prompt.c\
		 src/parse.c\
		 src/parse_1.c\
		 src/parse_2.c\
		 src/redirect.c\
		 src/exec.c\
		 src/script.c\
		 src/builtin/exit.c\
		 src/builtin/chdir.c\
		 src/builtin/unset.c\
		 src/builtin/export.c\
		 src/builtin/env.c\
		 src/builtin/pwd.c\
		 src/builtin/echo.c
OBJ		=$(SRC:src/%.c=obj/%.o)
LIB		=printf/ft_printf.a getnextline/get_next_line.a libft/libft.a

all:		libft getnextline printf $(NAME)

clean:
				@$(RM) -r obj
				@$(MAKE) -C libft clean > /dev/null
				@$(MAKE) -C printf clean > /dev/null
				@$(MAKE) -C getnextline clean > /dev/null
				@printf "\e[1;35mCleaned Object Files\n\e[0;00m"

fclean:		clean
				@$(RM) $(NAME)
				@$(MAKE) -C libft fclean > /dev/null
				@$(MAKE) -C printf fclean > /dev/null
				@$(MAKE) -C getnextline fclean > /dev/null
				@printf "\e[1;31mCleaned Executables\n\e[0;00m"

re:			fclean all

$(OBJ):		$(SRC)
				@mkdir -p $(dir $@)
				@printf "\e[1;34mBuilding $@\n\e[0;00m"
				@$(CC) $(CFLAGS) -c $(@:obj/%.o=src/%.c) -o $@

$(NAME):	$(OBJ)
				@printf "\e[1;36mCompiling $@\n\e[0;00m"
				@$(CC) $(CFLAGS) -lreadline $^ -o $@ $(LIB)
				@printf "\e[1;32mDone\e[0;00m\n"

libft:
				@$(MAKE) -C libft all

printf:
				@$(MAKE) -C printf all

getnextline:
				@$(MAKE) -C getnextline all

.PHONY:		all clean fclean re libft getnextline printf
