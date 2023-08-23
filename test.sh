# **************************************************************************** #
#                                                                              #
#                                                     .--.  _                  #
#    test.sh                                         |o_o || |                 #
#                                                    |:_/ || |_ _   ___  __    #
#    By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /    #
#                                                  (|     | )|_| |_| |>  <     #
#    Created: 2023/08/23 06:35:52 by djonker      /'\_   _/`\__|\__,_/_/\_\    #
#    Updated: 2023/08/23 09:52:52 by djonker      \___)=(___/                  #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

ERRORS=0
PASSES=0

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
		PASSES=$(($PASSES+1))
	else
		printf "\e[1;31mKO stdout doesn't match with command ${@} \nreal: $(cat realstdoutfile 2> /dev/null)\nmini: $(cat ministdoutfile 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	diff realerroutfile minierroutfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstderr OK \e[0;00m"
		PASSES=$(($PASSES+1))
	else
		printf "\n\e[1;31mKO stderr doesn't match with command ${@} \nreal: $(cat realstderrfile 2> /dev/null)\nmini: $(cat ministderrfile 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	if [ $REALRETURN -ne $MINIRETURN ]
	then
		printf "\n\e[1;31mKO Return doesn't match with command ${@} \nReal $REALRETURN\nMini $MINIRETURN\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mreturn OK\n\e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	rm realstdoutfile realerroutfile ministdoutfile minierroutfile
	#sleep 0.2
}

# Testing Lines

# echo
printf "\e[1;36mTesting echo\e[0;00m\n"
testfunction "echo hallo"
testfunction 'echo "hallo"'
testfunction "echo 'hallo'"
testfunction "echo -n hallo"
testfunction "echo -nnn hallo"
testfunction "echo -nnm hallo"
testfunction "echo -n -n hallo"
testfunction "echo -n hallo -n"

# pwd
printf "\e[1;36mTesting pwd\e[0;00m\n"
testfunction "pwd"
testfunction "pwd bla"
testfunction "pwd -wat"

# export
printf "\e[1;36mTesting export\e[0;00m\n"
testfunction "export"
testfunction "export bla=bla"
testfunction "export bla"
testfunction "export 0bla=bla"
testfunction "export -bla=bla"
testfunction "export _bla=bla"
testfunction "export _bla"
testfunction "export PATH=bahbah"

# unset
printf "\e[1;36mTesting unset\e[0;00m\n"
testfunction "unset bla"
testfunction "unset PATH"
testfunction "unset"
testfunction "unset -wat"

# env
printf "\e[1;36mTesting env\e[0;00m\n"
testfunction "env"
testfunction "env blabla"
testfunction "env -wat"

# exit
printf "\e[1;36mTesting exit\e[0;00m\n"
testfunction "exit"
testfunction "exit 1"
testfunction "exit 123"
testfunction "exit 256"
testfunction "exit bla"
testfunction "exit -wat"

# cd
printf "\e[1;36mTesting cd\e[0;00m\n"
testfunction "cd"
testfunction "cd .."
testfunction "cd ."
testfunction "cd ~"
testfunction "cd src"
testfunction "cd /etc"
testfunction "cd ~/Documents"
testfunction "cd nonexistingpath"

# Shutdown
printf "\e[1;36mThe tester found $ERRORS KO\'s and $PASSES OK\'s\e[0;00m\n"
exit $ERRORS
