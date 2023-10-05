# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                        |o_o || |                 #
#                                                      +:+                     #
#    By: djonker <djonker@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/19 15:20:20 by djonker       #+#    #+#                  #
#    Updated: 2023/10/05 19:35:26 by houtworm     \___)=(___/                  #
#                                                                              #
# **************************************************************************** #

NAME	=minishell
CC		=gcc
CFLAGS	=-Wall -Werror -Wextra -g #-fsanitize=address
RM		=rm -f
SRC		=src/main/main.c\
		 src/main/init.c\
		 src/main/prompt.c\
		 src/main/script.c\
		 src/main/signal.c\
		 src/main/mshrc.c\
		 src/main/history.c\
		 src/main/insults.c\
		 src/parse/parse.c\
		 src/parse/hashtag.c\
		 src/parse/syntax.c\
		 src/parse/pipe.c\
		 src/parse/alias.c\
		 src/parse/heredoc.c\
		 src/parse/quote.c\
		 src/parse/complete.c\
		 src/parse/condition.c\
		 src/parse/priority.c\
		 src/parse/redirect.c\
		 src/parse/variable.c\
		 src/parse/globs.c\
		 src/parse/globinit.c\
		 src/parse/globsub.c\
		 src/parse/globpoint.c\
		 src/parse/globtools.c\
		 src/parse/wildcard.c\
		 src/parse/joker.c\
		 src/parse/anyof.c\
		 src/exec/fork.c\
		 src/exec/priority.c\
		 src/exec/exec.c\
		 src/exec/dupmachine.c\
		 src/exec/verify.c\
		 src/builtin/builtin.c\
		 src/builtin/alias.c\
		 src/builtin/exit.c\
		 src/builtin/chdir.c\
		 src/builtin/unset.c\
		 src/builtin/export.c\
		 src/builtin/env.c\
		 src/builtin/pwd.c\
		 src/builtin/echo.c\
		 src/builtin/z.c\
		 src/builtin/period.c\
		 src/builtin/exec.c\
		 src/builtin/which.c\
		 src/tools/tools.c\
		 src/tools/error.c\
		 src/tools/print.c\
		 src/tools/env.c\
		 src/tools/cleanup.c
#src/parse/tools.c
#src/parse/parse_utils.c
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
				@$(CC) $(CFLAGS) $^ -o $@ $(LIB) -lreadline
				@printf "\e[1;32mDone\e[0;00m\n"

libft:
				@$(MAKE) -C libft all

printf:
				@$(MAKE) -C printf all

getnextline:
				@$(MAKE) -C getnextline all

.PHONY:		all clean fclean re libft getnextline printf
