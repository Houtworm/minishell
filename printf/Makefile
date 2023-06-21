# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                        |o_o || |                 #
#                                                      +:+                     #
#    By: djonker <marvin@codam.nl>                    +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/19 06:09:46 by djonker       #+#    #+#                  #
#    Updated: 2023/02/26 10:36:32 by houtworm     \___)=(___/                  #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
CC			= gcc
FC			= -Wall -Werror -Wextra# -fsanitize=address
RM			= rm -f
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
OS			= Freedom Respecting Linux! :)
SRC			= src/ft_printf.c \
				src/ft_printf_flags.c \
				src/ft_printf_length.c \
				src/Linux/ft_printf_proc_c.c \
				src/Linux/ft_printf_proc_s.c \
				src/Linux/ft_printf_proc_p.c \
			  	src/Linux/ft_printf_proc_d.c \
			  	src/Linux/ft_printf_proc_u.c \
			  	src/Linux/ft_printf_proc_x.c \
				src/Linux/ft_printf_proc_f.c \
				src/Linux/ft_printf_proc_g.c \
				src/Linux/ft_printf_proc_e.c \
				src/Linux/ft_printf_proc_o.c \
				src/Linux/ft_printf_proc_a.c \
				src/Linux/ft_printf_proc_b.c \
				src/Linux/ft_printf_proc_inf.c \
				src/Linux/ft_printf_proc_prec.c
else
OS			= Proprietary Malware :(
SRC			= src/ft_printf.c \
				src/ft_printf_flags.c \
				src/ft_printf_length.c \
				src/Mac/ft_printf_proc_c.c \
				src/Mac/ft_printf_proc_s.c \
				src/Mac/ft_printf_proc_p.c \
			  	src/Mac/ft_printf_proc_d.c \
			  	src/Mac/ft_printf_proc_u.c \
			  	src/Mac/ft_printf_proc_x.c \
				src/Mac/ft_printf_proc_f.c \
				src/Mac/ft_printf_proc_g.c \
				src/Mac/ft_printf_proc_e.c \
				src/Mac/ft_printf_proc_o.c \
				src/Mac/ft_printf_proc_a.c \
				src/Mac/ft_printf_proc_b.c \
				src/Mac/ft_printf_proc_inf.c \
				src/Mac/ft_printf_proc_prec.c
endif
OBJ			=$(SRC:src/%.c=obj/%.o)
FAR			=ar -src
LIB			=libft/libft.a

all:		libft/libft.a ft_printf.a $(NAME)

bonus:		all

printf:		libft/libft.a ft_printf.a

ft_printf.a:	libft/libft.a $(OBJ)
				@printf "\e[1;36mLinking $@\e[0;00m\n"
				@$(FAR) ft_printf.a $(OBJ) $(LIB) > /dev/null 2>&1
				@printf "\e[1;32mDone\e[0;00m\n"

clean:
				@$(RM) -r obj
				@$(MAKE) -C libft clean > /dev/null
				@printf "\e[1;35mCleaned Object Files\n\e[0;00m"

fclean:		clean
				@$(RM) $(NAME) ft_printf.a
				@$(MAKE) -C libft fclean > /dev/null
				@printf "\e[1;31mCleaned Executables\n\e[0;00m"

re:			fclean all

$(OBJ):		$(SRC)
				@mkdir -p $(dir $@)
				@printf "\e[1;34mBuilding $@\n\e[0;00m"
				@$(CC) $(CFLAGS) -c $(@:obj/%.o=src/%.c) -o $@

$(NAME):	libft/libft.a ft_printf.a $(OBJ)
				@printf "\e[1;36mLinking $@\e[0;00m\n"
				@cp libft/libft.a libftprintf.a
				@$(FAR) $(NAME) $(OBJ) > /dev/null 2>&1
				@printf "\e[1;32mDone\e[0;00m\n"

libft/libft.a:
				@$(MAKE) -C libft bonus 2> /dev/null

