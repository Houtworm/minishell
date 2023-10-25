# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: djonker <djonker@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/19 15:20:20 by djonker       #+#    #+#                  #
#    Updated: 2023/10/25 04:51:59 by djonker       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=minishell
CC		=gcc
CFLAGS	=-Wall -Werror -Wextra -g -fsanitize=address
RM		=rm -f
SRC		=src/main/main.c\
		 src/main/init.c\
		 src/main/prompt.c\
		 src/main/signal.c\
		 src/main/mshrc.c\
		 src/main/history.c\
		 src/main/insults.c\
		 src/parse/parse.c\
		 src/parse/hashtag.c\
		 src/parse/syntax.c\
		 src/parse/syntax2.c\
		 src/parse/pipe.c\
		 src/parse/alias.c\
		 src/parse/heredoc.c\
		 src/parse/heredoc2.c\
		 src/parse/quote.c\
		 src/parse/quote2.c\
		 src/parse/complete.c\
		 src/parse/condition.c\
		 src/parse/priority.c\
		 src/parse/outputfile.c\
		 src/parse/inputfile.c\
		 src/parse/inputfile2.c\
		 src/parse/variable.c\
		 src/parse/variable2.c\
		 src/parse/tilde.c\
		 src/parse/oldline.c\
		 src/exec/fork.c\
		 src/exec/substitution.c\
		 src/exec/substitution2.c\
		 src/exec/nonbuiltin.c\
		 src/exec/exec.c\
		 src/exec/dupmachine.c\
		 src/exec/redirect.c\
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
		 src/globs/globs.c\
		 src/globs/initglob.c\
		 src/globs/initsubdir.c\
		 src/globs/initparent.c\
		 src/globs/globsubdir.c\
		 src/globs/globpointer.c\
		 src/globs/globtools.c\
		 src/globs/wildcard.c\
		 src/globs/joker.c\
		 src/globs/anyof.c\
		 src/globs/subwildcard.c\
		 src/globs/subjoker.c\
		 src/globs/subanyof.c\
		 src/globs/globmatch.c\
		 src/tools/error.c\
		 src/tools/print.c\
		 src/tools/environment.c\
		 src/tools/cleanup.c
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
