# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    script.sh                                       |o_o || |                 #
#                                                      +:+                     #
#    By: djonker <djonker@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/23 06:35:52 by djonker       #+#    #+#                  #
#    Updated: 2023/10/02 17:11:54 by houtworm     \___)=(___/                  #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

echo Hello World!
printf "trunc seems to be working\n" > file
printf "appending too\n" >> file
echo "piping too\n" | cat >> file
cat file
