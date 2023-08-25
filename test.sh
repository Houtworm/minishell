# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    test.sh                                         |o_o || |                 #
#                                                      +:+                     #
#    By: djonker <djonker@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/23 06:35:52 by djonker       #+#    #+#                  #
#    Updated: 2023/08/25 06:06:41 by houtworm     \___)=(___/                  #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

ERRORS=0
PASSES=0
SLEEP=0

testfunction()
{
	bash -c "$1" > realstdoutfile 2> realerroutfile
	REALRETURN=$?
	./minishell -c "$1" > ministdoutfile 2> minierroutfile
	MINIRETURN=$?
	diff realstdoutfile ministdoutfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstdout OK \e[0;00m"
		PASSES=$(($PASSES+1))
	else
		printf "\e[1;31mKO stdout doesn't match with command ${1} \nreal: $(cat realstdoutfile 2> /dev/null)\nmini: $(cat ministdoutfile 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	diff realerroutfile minierroutfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstderr OK \e[0;00m"
		PASSES=$(($PASSES+1))
	else
		printf "\n\e[1;31mKO stderr doesn't match with command ${1} \nreal: $(cat realstderrfile 2> /dev/null)\nmini: $(cat ministderrfile 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	if [ $REALRETURN -ne $MINIRETURN ]
	then
		printf "\n\e[1;31mKO Return doesn't match with command ${1} \nReal $REALRETURN\nMini $MINIRETURN\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mreturn OK\n\e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	rm realstdoutfile realerroutfile ministdoutfile minierroutfile
	sleep $SLEEP
}

redirectfunction()
{
	echo 1 > m1; echo 1 > r1; echo 2 > m2; echo 2 > r2; echo 3 > r3; echo 3 > m3;
	bash -c "$1" > realstdoutfile 2> realerroutfile
	REALRETURN=$?
	./minishell -c "$2" > ministdoutfile 2> minierroutfile
	MINIRETURN=$?
	diff realstdoutfile ministdoutfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstdout OK \e[0;00m"
		PASSES=$(($PASSES+1))
	else
		printf "\e[1;31mKO stdout doesn't match with command ${1} \nreal: $(cat realstdoutfile 2> /dev/null)\nmini: $(cat ministdoutfile 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	diff realerroutfile minierroutfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstderr OK \e[0;00m"
		PASSES=$(($PASSES+1))
	else
		printf "\n\e[1;31mKO stderr doesn't match with command ${1} \nreal: $(cat realstderrfile 2> /dev/null)\nmini: $(cat ministderrfile 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	if [ $REALRETURN -ne $MINIRETURN ]
	then
		printf "\n\e[1;31mKO Return doesn't match with command ${1} \nReal $REALRETURN\nMini $MINIRETURN\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mreturn OK\n\e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	cat m1 2> /dev/null 1>&2
	if [ $? -ne 0 ]
	then
		diff r1 m1 2> /dev/null
		if [ $? -ne 0 ]
		then
			printf "\n\e[1;31mKO file 1 doesn't match with command ${1} \nreal: $(cat r1 2> /dev/null)\nmini: $(cat m1 2> /dev/null)\e[0;00m\n"
			ERRORS=$(($ERRORS+1))
		fi
	else
		printf "\e[1;32mFile 1 OK\n\e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	cat m2 2> /dev/null 1>&2
	if [ $? -ne 0 ]
	then
		diff r2 m2 2> /dev/null
		if [ $? -ne 0 ]
		then
			printf "\n\e[1;31mKO file 2 doesn't match with command ${1} \nreal: $(cat r2 2> /dev/null)\nmini: $(cat m2 2> /dev/null)\e[0;00m\n"
			ERRORS=$(($ERRORS+1))
		fi
	else
		printf "\e[1;32mFile 2 OK\n\e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	cat m3 2> /dev/null 1>&2
	if [ $? -ne 0 ]
	then
		diff r3 m3 2> /dev/null
		if [ $? -ne 0 ]
		then
			printf "\n\e[1;31mKO file 3 doesn't match with command ${1} \nreal: $(cat r3 2> /dev/null)\nmini: $(cat m3 2> /dev/null)\e[0;00m\n"
			ERRORS=$(($ERRORS+1))
		fi
	else
		printf "\e[1;32mFile 3 OK\n\e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	rm realstdoutfile realerroutfile ministdoutfile minierroutfile r1 r2 r3 m1 m2 m3 2> /dev/null
	sleep $SLEEP
}

# Testing Lines

# echo
#printf "\e[1;36mTesting echo\e[0;00m\n"
#testfunction "echo hallo"
#testfunction 'echo "hallo"'
#testfunction "echo 'hallo'"
#testfunction "echo -n hallo"
#testfunction "echo -nnn hallo"
#testfunction "echo -nnm hallo"
#testfunction "echo -n -n hallo"
#testfunction "echo -n hallo -n"

# pwd
#printf "\e[1;36mTesting pwd\e[0;00m\n"
#testfunction "pwd"
#testfunction "pwd bla"
#testfunction "pwd -wat"

# export
#printf "\e[1;36mTesting export\e[0;00m\n"
#testfunction "export"
#testfunction "export bla=bla"
#testfunction "export bla"
#testfunction "export 0bla=bla"
#testfunction "export -bla=bla"
#testfunction "export _bla=bla"
#testfunction "export _bla"
#testfunction "export PATH=bahbah"

# unset
#printf "\e[1;36mTesting unset\e[0;00m\n"
#testfunction "unset bla"
#testfunction "unset PATH"
#testfunction "unset"
#testfunction "unset -wat"

# env
#printf "\e[1;36mTesting env\e[0;00m\n"
#testfunction "env"
#testfunction "env blabla"
#testfunction "env -wat"

# exit
#printf "\e[1;36mTesting exit\e[0;00m\n"
#testfunction "exit"
#testfunction "exit 1"
#testfunction "exit 123"
#testfunction "exit 256"
#testfunction "exit bla"
#testfunction "exit -wat"

# cd
#printf "\e[1;36mTesting cd\e[0;00m\n"
#testfunction "cd"
#testfunction "cd .."
#testfunction "cd ."
#testfunction "cd ~"
#testfunction "cd src"
#testfunction "cd /etc"
#testfunction "cd ~/Documents"
#testfunction "cd nonexistingpath"

# redirections
printf "\e[1;36mTesting redirections\e[0;00m\n"
redirectfunction "cat < r1 < r2 > r3" "cat < m1 < m2 > m3"
redirectfunction "cat r1 > r2 > r3" "cat m1 > m2 > m3"
redirectfunction "r1 < cat > r2 > r3" "m1 < cat > m2 > m3"

# and operator
printf "\e[1;36mTesting and operator\e[0;00m\n"
testfunction "ls && echo 'hello'"
testfunction "ls &&echo 'hello'"
testfunction "ls&&echo 'hello'"
testfunction "ls&&&echo 'hello'"
testfunction "ls&& &echo 'hello'"
testfunction "ls&&;echo 'hello'"
testfunction "ls&& ;echo 'hello'"

# Shutdown
printf "\e[1;36mThe tester found $ERRORS KO\'s and $PASSES OK\'s\e[0;00m\n"
exit $ERRORS
