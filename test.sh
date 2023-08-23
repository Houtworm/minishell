# **************************************************************************** #
#                                                                              #
#                                                     .--.  _                  #
#    test.sh                                         |o_o || |                 #
#                                                    |:_/ || |_ _   ___  __    #
#    By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /    #
#                                                  (|     | )|_| |_| |>  <     #
#    Created: 2023/08/23 06:35:52 by djonker      /'\_   _/`\__|\__,_/_/\_\    #
#    Updated: 2023/08/23 07:07:35 by djonker      \___)=(___/                  #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

testfunction()
{
	bash -c $@ > realstdoutfile 2> realerroutfile
	REALRETURN=$?
	./minishell -c $@ > ministdoutfile 2> minierroutfile
	MINIRETURN=$?
	diff realstdoutfile ministdoutfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mOK \e[0;00m"
	else
		printf "\n\e[1;31mKO stdout doesn't match $@\e[0;00m\n\n"
		printf real: 
		cat realstdoutfile
		printf mini: 
		cat ministdoutfile
	fi
	diff realerroutfile minierroutfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mOK \e[0;00m"
	else
		printf "\n\e[1;31mKO stderr doesn't match $@\e[0;00m\n\n"
		printf real: 
		cat realerroutfile
		printf mini: 
		cat minierroutfile
	fi
	if [ $REALRETURN -ne $MINIRETURN ]
	then
		printf "\n\e[1;31mKO Return doesn't match\nReal $REALRETURN\nMini $MINIRETURN\e[0;00m\n"
	else
		printf "\e[1;32mOK \e[0;00m"
	fi
	rm realstdoutfile realerroutfile ministdoutfile minierroutfile
}

testfunction echo hallo
testfunction echo -n hallo
testfunction env
