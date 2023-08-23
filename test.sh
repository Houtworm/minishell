# **************************************************************************** #
#                                                                              #
#                                                     .--.  _                  #
#    test.sh                                         |o_o || |                 #
#                                                    |:_/ || |_ _   ___  __    #
#    By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /    #
#                                                  (|     | )|_| |_| |>  <     #
#    Created: 2023/08/23 06:35:52 by djonker      /'\_   _/`\__|\__,_/_/\_\    #
#    Updated: 2023/08/23 07:56:25 by djonker      \___)=(___/                  #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

testfunction()
{
	bash -c "$@" > realstdoutfile 2> realerroutfile
	REALRETURN=$?
	./minishell -c "$@" > ministdoutfile 2> minierroutfile
	MINIRETURN=$?
	diff realstdoutfile ministdoutfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstdout OK \e[0;00m"
	else
		printf "\n\e[1;31mKO stdout doesn't match with command ${@} \nreal: $(cat realstdoutfile)\nmini: $(cat ministdoutfile)\e[0;00m\n"
	fi
	diff realerroutfile minierroutfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstderr OK \e[0;00m"
	else
		printf "\n\e[1;31mKO stderr doesn't match with command ${@} \nreal: $(cat realstderrfile)\nmini: $(cat ministderrfile)\e[0;00m\n"
	fi
	if [ $REALRETURN -ne $MINIRETURN ]
	then
		printf "\n\e[1;31mKO Return doesn't match with command ${@} \nReal $REALRETURN\nMini $MINIRETURN\e[0;00m\n"
	else
		printf "\e[1;32mreturn OK\n\e[0;00m"
	fi
	rm realstdoutfile realerroutfile ministdoutfile minierroutfile
	sleep 0.2
}

testfunction "echo hallo"
testfunction 'echo "hallo"'
testfunction "echo 'hallo'"
testfunction "echo -n hallo"
testfunction "echo -nnn hallo"
testfunction "echo -nnm hallo"
testfunction "echo -n -n hallo"

