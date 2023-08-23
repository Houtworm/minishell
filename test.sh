# **************************************************************************** #
#                                                                              #
#                                                     .--.  _                  #
#    test.sh                                         |o_o || |                 #
#                                                    |:_/ || |_ _   ___  __    #
#    By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /    #
#                                                  (|     | )|_| |_| |>  <     #
#    Created: 2023/08/23 06:35:52 by djonker      /'\_   _/`\__|\__,_/_/\_\    #
#    Updated: 2023/08/23 06:56:43 by djonker      \___)=(___/                  #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

testfunction()
{
	bash -c $@ > realstdoutfile
	REALRETURN=$?
	minishell -c $@ > ministdoutfile
	MINIRETURN=$?
	if [ "$REALOUTPUT" != "$MINIOUTPUT" ]
	then
		printf "\n\e[1;31mKO Output doesn't match\nReal $REALOUTPUT\nMini $MINIOUTPUT\e[0;00m\n"
	else
		printf "\e[1;32mOK \e[0;00m"
	fi
	if [ $REALRETURN -ne $MINIRETURN ]
	then
		printf "\n\e[1;31mKO Return doesn't match\nReal $REALRETURN\nMini $MINIRETURN\e[0;00m\n"
	else
		printf "\e[1;32mOK \e[0;00m"
	fi
}

testfunction echo hallo
testfunction echo -n hallo
