# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    test.sh                                         |o_o || |                 #
#                                                      +:+                     #
#    By: djonker <djonker@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/23 06:35:52 by djonker       #+#    #+#                  #
#    Updated: 2023/09/13 17:34:01 by houtworm     \___)=(___/                  #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

ERRORS=0
PASSES=0
SLEEP=0

testfunction()
{
	timeout 2 bash -c "$1" > realstdoutfile 2> realstderrfile
	REALRETURN=$?
	timeout 2 ./minishell -c "$1" > ministdoutfile 2> ministderrfile
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
	diff realstderrfile ministderrfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstderr OK \e[0;00m"
		PASSES=$(($PASSES+1))
	else
		printf "\n\e[1;31mKO stderr doesn't match with command ${1} \nreal: $(cat realstderrfile)\nmini: $(cat ministderrfile)\e[0;00m\n"
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
	rm realstdoutfile realstderrfile ministdoutfile ministderrfile
	sleep $SLEEP
}

redirectfunction()
{
	echo 1 > m1; echo 1 > r1; echo 2 > m2; echo 2 > r2; echo 3 > r3; echo 3 > m3;
	bash -c "$1" > realstdoutfile 2> realstderrfile
	REALRETURN=$?
	./minishell -c "$2" > ministdoutfile 2> ministderrfile
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
	diff realstderrfile ministderrfile > /dev/null
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
	diff r1 m1 > /dev/null
	if [ $? -ne 0 ]
	then
		printf "\n\e[1;31mKO file 1 doesn't match with command ${1} \nreal: $(cat r1 2> /dev/null)\nmini: $(cat m1 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mFile 1 OK\n\e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	diff r2 m2 > /dev/null
	if [ $? -ne 0 ]
	then
		printf "\n\e[1;31mKO file 2 doesn't match with command ${1} \nreal: $(cat r2 2> /dev/null)\nmini: $(cat m2 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mFile 2 OK\n\e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	diff r3 m3 > /dev/null
	if [ $? -ne 0 ]
	then
		printf "\n\e[1;31mKO file 3 doesn't match with command ${1} \nreal: $(cat r3 2> /dev/null)\nmini: $(cat m3 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mFile 3 OK\n\e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	rm realstdoutfile realstderrfile ministdoutfile ministderrfile r1 r2 r3 m1 m2 m3 2> /dev/null
	sleep $SLEEP
}

environmentfunction()
{
	timeout 2 bash -c "$1" | grep "$2" > realstdoutfile 2> realstderrfile
	REALRETURN=$?
	timeout 2 ./minishell -c "$1" | grep "$2" > ministdoutfile 2> ministderrfile
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
	diff realstderrfile ministderrfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstderr OK \e[0;00m"
		PASSES=$(($PASSES+1))
	else
		printf "\n\e[1;31mKO stderr doesn't match with command ${1} \nreal: $(cat realstderrfile)\nmini: $(cat ministderrfile)\e[0;00m\n"
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
	rm realstdoutfile realstderrfile ministdoutfile ministderrfile
	sleep $SLEEP
}

# Testing Lines

# basic
printf "\e[1;36mTesting basics\e[0;00m\n"
testfunction ""
testfunction "\"\""
testfunction ".."
testfunction "hallo"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
touch perm
chmod 000 perm
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
chmod 444 perm
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
chmod 666 perm
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
chmod 777 perm
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
rm perm
testfunction "echo \$SHLVL"
testfunction "echo \$?"
testfunction "echo \$PWD"

# echo
printf "\e[1;36mTesting echo\e[0;00m\n"
testfunction "echo"
testfunction "echo hallo"
testfunction 'echo "hallo"'
testfunction "echo 'hallo'"
testfunction "echo -n hallo"
testfunction "echo -nnn hallo"
testfunction "echo -nnm hallo"
testfunction "echo -n -n hallo"
testfunction "echo -n -m hallo"
testfunction "echo -n -n -n -n -n -n -n -n hallo"
testfunction "echo -n hallo -n"
testfunction "echo \$FAKEVAR"
testfunction "echo \$PATH"
testfunction "echo ~"
testfunction "echo \"bip | bip ; coyotte > < \""
testfunction "echo \\>"
testfunction "export var=\"\$USER\" && echo \$USER\$var\$USER\$USER\$USERtest\$USER"
testfunction "echo \"\\s\""
testfunction "echo \"\\\\s\""
testfunction "echo bounjour \\; ls"
testfunction "echo \"12\""
testfunction "echo \"hey\"J"
testfunction "echo \"hey\"\$PATH"
testfunction "echo \"hey\"&"
testfunction "echo \"hey\"\"hey\""

 # variable
printf "\e[1;36mTesting \$VAR variable\e[0;00m\n"
testfunction "echo \$SHLVL\"\$SHLVL\"\$SHLVL'\$SHLVL'\$SHLVL"
testfunction "printf \$FAKEVAR"
testfunction "printf \$SHLVL"
testfunction "printf \$PWD"
testfunction "printf \$?"

# export
printf "\e[1;36mTesting export\e[0;00m\n"
environmentfunction "export" "SHLVL"
testfunction "export bla=bla"
environmentfunction "export bla=bla" "bla"
testfunction "export bla"
environmentfunction "export bla" "bla"
testfunction "export 0bla=bla"
environmentfunction "export 0bla=bla" "0bla"
testfunction "export -bla=bla"
environmentfunction "export -bla=bla" "-bla"
testfunction "export _bla=bla"
environmentfunction "export _bla=bla" "_bla"
testfunction "export _bla"
environmentfunction "export _bla" "_bla"
testfunction "export PATH=bahbah"
environmentfunction "export PATH=bahbah" "PATH"
testfunction "export arg=\"-la\" && ls \$arg"
testfunction "export arg=a && export \$var=test && echo \$var \$a"
testfunction "export \$abc=a && unset abc"
environmentfunction "export \$abc=a && unset abc" "abc"
environmentfunction "export test1" "test1"
environmentfunction "export test2=" "test2"
environmentfunction "export varra=hallo" "varra"
testfunction "export \"\" tester=b"
environmentfunction "export test3=\$HOME" "test3"

# unset
printf "\e[1;36mTesting unset\e[0;00m\n"
testfunction "unset notexistant"
testfunction "unset PATH"
testfunction "unset"
testfunction "unset -wat"
environmentfunction "unset PATH" "PATH"
environmentfunction "unset SHLVL" "SHLVL"
environmentfunction "unset PWD" "PWD"

# env
printf "\e[1;36mTesting env\e[0;00m\n"
testfunction "env blabla"
testfunction "env -wat"
environmentfunction "env" "SHLVL"
environmentfunction "env blabla" "SHLVL"
environmentfunction "env -wat" "SHLVL"
testfunction "env | grep OLDPWD"

# exit
printf "\e[1;36mTesting exit\e[0;00m\n"
testfunction "exit"
testfunction "exit 1"
testfunction "exit 123"
testfunction "exit 256"
testfunction "exit bla"
testfunction "exit -wat"
testfunction "exit 9223372036854775807"
testfunction "exit 9223372036854775808"
testfunction "exit -9223372036854775807"
testfunction "exit -9223372036854775808"
testfunction "exit -9223372036854775809"

# cd and pwd
printf "\e[1;36mTesting cd and pwd\e[0;00m\n"
testfunction "cd"
testfunction "mkdir a && mkdir a/b && cd a/b && rm -fr ../../a && cd .."
testfunction "cd && pwd"
testfunction "cd .."
testfunction "cd .. && pwd"
testfunction "cd .. bla"
testfunction "cd .. bla && pwd"
testfunction "cd ../../../../../../../../../.."
testfunction "cd ../../../../../../../../../.. && pwd"
testfunction "cd ."
testfunction "cd . && pwd"
testfunction "cd ~"
testfunction "cd ~ && pwd"
testfunction "unset HOME && cd ~"
testfunction "unset HOME && cd ~ && pwd"
testfunction "export HOME=/home/user42 && cd ~"
testfunction "export HOME=/home/user42 && cd ~ && pwd"
testfunction "cd -"
testfunction "cd - && pwd"
testfunction "cd src && cd -"
testfunction "cd src && cd - && pwd"
testfunction "cd src"
testfunction "cd src && pwd"
testfunction "cd /etc"
testfunction "cd /etc && pwd"
testfunction "cd ~/Documents"
testfunction "cd ~/Documents && pwd"
testfunction "cd nonexistingpath"
testfunction "cd nonexistingpath && pwd"
testfunction "pwd"
testfunction "pwd bla"
testfunction "pwd -wat"

# > trunctuate
printf "\e[1;36mTesting > trunctuate \e[0;00m\n"
testfunction ">"
redirectfunction "cat r1 > r2 > r3" "cat m1 > m2 > m3"
redirectfunction "printf 'blabla' > r1; printf 'blabla' > r2; printf 'blabla' > r3" "printf 'blabla' > m1; printf 'blabla' > m2; printf 'blabla' > m3"
redirectfunction "printf 'blabla' > r1 && printf 'blabla' > r2 && printf 'blabla' > r3" "printf 'blabla' > m1 && printf 'blabla' > m2 && printf 'blabla' > m3"
redirectfunction "echo \"hoi\" > | r1" "echo \"hoi\" > | m1"
redirectfunction "echo \"hoi\" >| r1" "echo \"hoi\" > | m1"
redirectfunction "> r1 | echo blabla" "> m1 | echo blabla"
redirectfunction "exit > r1" "exit > m1"
redirectfunction "cd .. > r1" "cd .. > m1"
redirectfunction "> r1" "> m1"
redirectfunction "echo 2 > r1 > r2" "echo 2 > m1 > m2"
redirectfunction "echo 2 > r1 > r2" "echo 2 > m1 > m2"
redirectfunction "echo test > r1 r2" "echo test > m1 m2"
redirectfunction "Non_exist_cmd > r1" "Non_exist_cmd > m1"

# >> append
printf "\e[1;36mTesting >> append \e[0;00m\n"
testfunction ">>"
redirectfunction "cat r1 >> r2 >> r3" "cat m1 >> m2 >> m3"
redirectfunction "printf 'blabla' >> r1; printf 'blabla' >> r2; printf 'blabla' >> r3" "printf 'blabla' >> m1; printf 'blabla' >> m2; printf 'blabla' >> m3"
redirectfunction "printf 'blabla' >> r1 && printf 'blabla' >> r2 && printf 'blabla' >> r3" "printf 'blabla' >> m1 && printf 'blabla' >> m2 && printf 'blabla' >> m3"
redirectfunction "echo \"hoi\" >> | r1" "echo \"hoi\" >> | m1"
redirectfunction "echo \"hoi\" >>| r1" "echo \"hoi\" >> | m1"
redirectfunction ">> r1 | echo blabla" ">> m1 | echo blabla"
redirectfunction "exit >> r1" "exit >> m1"
redirectfunction "cd .. >> r1" "cd .. >> m1"
redirectfunction ">> r1" ">> m1"
redirectfunction "echo 2 >> r1 >> r2" "echo 2 >> m1 >> m2"
redirectfunction "echo 2 >> r1 >> r2" "echo 2 >> m1 >> m2"
redirectfunction "echo test >> r1 r2" "echo test >> m1 m2"
redirectfunction "Non_exist_cmd >> r1" "Non_exist_cmd >> m1"

# < input from
printf "\e[1;36mTesting < input from \e[0;00m\n"
testfunction "<"
redirectfunction "cat < r1" "cat < m1"

# << heredoc
printf "\e[1;36mTesting << heredoc \e[0;00m\n"
testfunction "<<"
testfunction "cat << EOF
t e s t
EOF
"
testfunction "cat << EOF
t e s t
EOF"
testfunction "cat << EOF
t e s t
EOF 
EOF
"
testfunction "cat << EOF
t e s t
 EOF
EOF
"
testfunction "echo << EOF
t e s t
EOF
"
testfunction "echo << EOF
t e s t
EOF"
testfunction "echo << EOF
t e s t
EOF 
EOF
"
testfunction "echo << EOF
t e s t
 EOF
EOF
"

# <<< herestring
printf "\e[1;36mTesting <<< herestring \e[0;00m\n"
testfunction "<<<"

# < << >> > redirection combinations
printf "\e[1;36mTesting < << >> > redirection combinations \e[0;00m\n"
redirectfunction "r1 < cat > r2 > r3" "m1 < cat > m2 > m3"
redirectfunction "cat -e > r1 < r2" "cat -e > m1 < m2"
redirectfunction "cat < r1 < r2 > r3" "cat < m1 < m2 > m3"
#redirectfunction "< r1 cat | << EOF cat | cat >> r3" "< m1 cat | << EOF cat | cat >> m3"

# ; Command end
printf "\e[1;36mTesting ; command end\e[0;00m\n"
testfunction ";"
testfunction "echo hello ; echo 'hello'"
testfunction "echo hello ;echo 'hello'"
testfunction "echo hello;echo 'hello'"
testfunction "echo hello;;echo 'hello'"
testfunction "echo hello; ;echo 'hello'"
testfunction "echo hello&&;echo 'hello'"
testfunction "echo hello&& ;echo 'hello'"
testfunction "echo hello||;echo 'hello'"
testfunction "echo hello|| ;echo 'hello'"
testfunction "sleep 1 ; sleep 1 ; sleep 1"

# && and operator
printf "\e[1;36mTesting && and operator\e[0;00m\n"
testfunction "&&"
testfunction "echo hello && echo 'hello'"
testfunction "echo hello &&echo 'hello'"
testfunction "echo hello&&echo 'hello'"
testfunction "echo hello&&&echo 'hello'"
testfunction "echo hello&& &echo 'hello'"
testfunction "echo hello&&;echo 'hello'"
testfunction "echo hello&& ;echo 'hello'"
testfunction "sleep 1 && sleep 1 && sleep 1"

# || or operator
printf "\e[1;36mTesting || or operator\e[0;00m\n"
testfunction "||"
testfunction "echo hello || echo 'hello'"
testfunction "echo hello ||echo 'hello'"
testfunction "echo hello||echo 'hello'"
testfunction "echo hello|||echo 'hello'"
testfunction "echo hello|| &echo 'hello'"
testfunction "echo hello||;echo 'hello'"
testfunction "echo hello|| ;echo 'hello'"
testfunction "sleep 1 || sleep 1 || sleep 1"

# $VAR variables
printf "\e[1;36mTesting \$VAR variables\e[0;00m\n"
testfunction "$"
testfunction "echo \$''"
testfunction "echo \$PWD"
testfunction "echo \$?"
testfunction "echo \$DOESNOTEXIST"
testfunction "\$DOESNOTEXIST"
testfunction "cd \$HOME"
testfunction "ls \$HOME"

# piping
printf "\e[1;36mTesting piping\e[0;00m\n"
testfunction "|"
testfunction "cat /dev/random | head -n 1"
testfunction "sleep 1 | sleep 1 | sleep 1"
testfunction "cat Makefile | grep pr | head -n 5 | hello"
testfunction "cat Makefile | grep pr | head -n 5 | cd file_not_exit"
testfunction "ls | exit"

# quotes
printf "\e[1;36mTesting quotes\e[0;00m\n"
testfunction "''"
testfunction "printf \"hallo\""
testfunction "printf 'hallo'"
testfunction "printf ''\"hallo\"''"
testfunction "printf \"'\"hallo\"'\""
testfunction "printf '\"'\"hallo\"'\"'"
testfunction "echo '\"abc\"'"
testfunction "echo \"\" bonjour"

# open " quotes
printf "\e[1;36mTesting \" open quotes\e[0;00m\n"
testfunction "\""
testfunction "printf \"hallo
hallo\""
testfunction "printf \"
\""
testfunction "printf \"hallo
\"\"hallo
\"\"hallo
\""
testfunction "printf \"hallo
\"\"hallo
\"   \"hallo
\""
testfunction "printf '\"hallo'\"
\""

# open ' quotes
printf "\e[1;36mTesting ' open quotes\e[0;00m\n"
testfunction "'"
testfunction "printf 'hallo
hallo'"
testfunction "printf '
'"
testfunction "printf 'hallo
''hallo
''hallo
'"
testfunction "printf 'hallo
''hallo
'   'hallo
'"

# ( open parenthesis
printf "\e[1;36mTesting ( open parenthesis\e[0;00m\n"
testfunction "("
testfunction "printf \$(echo hallo
hallo)"
testfunction "printf \$(nfsbgdf
)"
testfunction "printf \$(echo hallo
)"hallo
testfunction "printf \$(
)"
testfunction "printf \$(echo hallo
) && echo \$(echo hallo
)"

# ` open backticks
printf "\e[1;36mTesting \` open backticks\e[0;00m\n"
testfunction "\`"
testfunction "printf \`echo hallo
hallo\`"
testfunction "printf \`nfsbgdf
\`"
testfunction "printf \`echo hallo
\`"hallo
testfunction "printf \`
\`"
testfunction "printf \`(echo hallo
\` && echo \`echo hallo
\`"

# (`"' open combinations
printf "\e[1;36mTesting (\`\'\" open combinations\e[0;00m\n"
testfunction "printf \`echo hallo
hallo\` && \$(echo hallo
) || echo \"hallo
\""
testfunction "printf \`echo 'hallo
hallo'\`"
testfunction "printf \$(echo 'hallo
hallo')"
testfunction "printf \`echo \"hallo
hallo\"\`"
testfunction "printf \$(echo \"hallo
hallo\")"

# * wildcards
printf "\e[1;36mTesting * Wildcards\e[0;00m\n"
testfunction "*"
testfunction "ls *rc"
testfunction "ls *r*"
testfunction "ls *rc/b*"
testfunction "ls g*t*e*t*i*e"
testfunction "ls *e*n*x*l*n*"
testfunction "ls ../*/src/*/*.c"
testfunction "ls ../*/src/doesnotexist/echo.c"
testfunction "ls ../*/src/builtin/fake.c"

# ? joker
printf "\e[1;36mTesting ? Jokers\e[0;00m\n"
testfunction "?"
testfunction "ls ?rc"
testfunction "ls ?r?"
testfunction "ls ?rc/???????"
testfunction "ls g?t?e?t?i?e"
testfunction "ls ?e?n?x?l?n?"
testfunction "ls ???/??iltin/echo.?"
testfunction "ls ???/??iltin/ekho.?"
testfunction "ls ?rc?/???????"

# [] anyof
printf "\e[1;36mTesting [] anyof\e[0;00m\n"
testfunction "[]"
testfunction "ls [s]rc"
testfunction "ls [so][rb][cj]"
testfunction "ls [so][rb][cj]/builtin"
testfunction "ls [so][rb][cj]/builtin/e[cx][hi][ot].[co]"
testfunction "ls [so][qa][cj]/builtin"
testfunction "ls [so][rb][cj]/builtin/echo.[rb]"

# glob combinations
printf "\e[1;36mTesting glob combinations \e[0;00m\n"
testfunction "ls [so]?[cj]/b??*/*[.,]?"

# # comments
printf "\e[1;36mTesting # comments\e[0;00m\n"
testfunction "#"
testfunction "printf \"hallo hallo\" #&& echo hallo"
testfunction "printf \"hallo hallo\"# && echo hallo"
testfunction "printf \"hallo hallo\"#&& echo hallo"
testfunction "printf \"hallo hallo\" # && echo hallo"
testfunction "printf \"hallo hallo\" #|| echo hallo"
testfunction "printf \"hallo hallo\"# || echo hallo"
testfunction "printf \"hallo hallo\"#|| echo hallo"
testfunction "printf \"hallo hallo\" # || echo hallo"
testfunction "printf \"hallo hallo\" #| echo hallo"
testfunction "printf \"hallo hallo\"# | echo hallo"
testfunction "printf \"hallo hallo\"#| echo hallo"
testfunction "printf \"hallo hallo\" # | echo hallo"
testfunction "printf \"hallo hallo\" #; echo hallo"
testfunction "printf \"hallo hallo\"# ; echo hallo"
testfunction "printf \"hallo hallo\"#; echo hallo"
testfunction "printf \"hallo hallo\" # ; echo hallo"
testfunction "printf \"hallo hallo # hallo\"; echo hallo"
testfunction "printf 'hallo hallo # hallo'; echo hallo"
testfunction "echo hallo hallo # hallo; echo hallo"

# `` backticks
printf "\e[1;36mTesting \`\` backticks\e[0;00m\n"
testfunction "\`\`"
testfunction "printf \`echo hallo\`"
testfunction "printf \"\`echo hallo\`\""
testfunction "printf '\`echo hallo\`'"
testfunction "printf '\`echo hallo\`e'"
testfunction "printf '\`echo hallo\`'e"
testfunction "printf 'e\`echo hallo\`'"
testfunction "printf e'\`echo hallo\`'"
testfunction "printf \"\`echo hallo\`e\""
testfunction "printf \"\`echo hallo\`\"e"
testfunction "printf \"e\`echo hallo\`\""
testfunction "printf e\"\`echo hallo\`\""

# $() Command Substitution
printf "\e[1;36mTesting \$() command substitution \e[0;00m\n"
testfunction "\$()"
testfunction "printf \$(echo hallo)"
testfunction "printf \"\$(echo hallo)\""
testfunction "printf '\$(echo hallo)'"
testfunction "printf '\$(echo hallo)e'"
testfunction "printf '\$(echo hallo)'e"
testfunction "printf 'e\$(echo hallo)'"
testfunction "printf e'\$(echo hallo)'"
testfunction "printf \"\$(echo hallo)e\""
testfunction "printf \"\$(echo hallo)\"e"
testfunction "printf \"e\$(echo hallo)\""
testfunction "printf e\"\$(echo hallo)\""

# Syntax errors
printf "\e[1;36mTesting Syntax errors \e[0;00m\n"
testfunction "<>"
testfunction "><"

# Shutdown
printf "\e[1;36mThe tester found $ERRORS KO's and $PASSES OK's\e[0;00m\n"
exit $ERRORS
