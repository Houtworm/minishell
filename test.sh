#!/bin/bash

testfunction()
{
	REALOUTPUT=$(bash $1)
	REALRETURN=$?
	MINIOUTPUT=$(./minishell $1)
	MINIRETURN=$?
	if [ $REALOUTPUT != $MINIOUTPUT ]
	then
		printf "\n\e[1;31mKO Output doesn't match\nReal $REALOUTPUT\nMini $MINIOUTPUT\e[0;00m\n"
	else
		printf "\e[1;32mOK \e[0;00m]]"
	fi
	if [ $REALRETURN -ne $MINIRETURN ]
	then
		printf "\n\e[1;31mKO Return doesn't match\nReal $REALRETURN\nMini $MINIRETURN\e[0;00m\n"
	else
		printf "\e[1;32mOK \e[0;00m]]"
	fi
}

testfunction "echo hallo"
testfunction "echo -n hallo"
