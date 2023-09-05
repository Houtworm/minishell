# Minishell
is a lightweight implementation of bash

---
## Features
#### Mandatory
- ```CTRL + C```
- ```CTRL + \```
- ```CTRL + D```
- ```Handle History```
- ```SHLVL +1 at launch```
- ```| pipes```
- ```> trunctuate```
- ```>> append```
- ```<```
- ```<< heredoc```
- ```"" quotes```
- ```'' quotes```
- ```$VAR```
- ```echo```
- ```env```
- ```pwd```
- ```cd```
- ```export```
- ```unset```
- ```exit```
#### Bonus
- ```&&```
- ```||```
- ```*```
#### Extra
- ```Prompt with return code, execution time, and other cool things :)```
- ```-d debug mode```
- ```Multiline History```
- ```History file```
- ```~/.mshrc parsing```
- ```handle -c argument```
- ```handle script as argument```
- ```CTRL + Z```
- ```handling non closed quotes```
- ```handling conditions with no command```
- ```;```
- ```&```
- ```$(command)```
- ``` `command` ```
- ```?```
- ```[]```
- ```#```
- ```alias```
- ```z```

---
## Todo
#### Environment
- Show prompt
- Handle history
- Parse ~/.mshrc
- SHLVL +1 at launch

#### Signals
- ```^C``` should break the readline
- ```^\``` shouldn't print anything
- ```^D``` should send EOF
- ```^Z``` should push to background

#### Parser
1. Split on pipes and create an additional fork struct for every pipe
2. ignoring text inside quotes split on command end ```;```
3. ignoring text inside quotes split on & to know if it has to be pushed to the background.
4. ignoring text inside quotes split on && and || and assign the correct condition to the next cmd struct in the current fork struct.
5. ignoring text inside quotes, expand *, ? and []
5. ignoring text inside single quotes, expand $VAR
6. ignoring text inside quotes set the right fds and redirections for ```<, > and >>```
7. ignoring text inside quotes set the redirection to heredoc or herestring for ```<< and <<<```
8. ignoring text inside quotes check for $(command) and `command` and put it at the front of the cmd struct
9. finally get the absolute path for the main command and split the rest of the command on the space for execve

#### Exec
1. save starting time
2. prepare the pipes for every fork
3. save stdin and stdout
4. create a child for every fork struct. unless there is only 1 fork struct then skip step 5
5. every child will run every cmd struct in their fork struct.
6. check for builtin and run them.
7. run the dupmachine, and set the source and destination of the in/output.
8. if it is a file run some checks on it, if it is a file, pipe or stdin/out set the correct fd. or call heredoc
9. execute the command.
10. somehow terminate a foreground process if the next command says it had enough example: cat /dev/random | head -n 100
11. wait for exit of child and pass the return code back
12. write return code to $?

### Builtins
#### cd
- cd
- cd ..
- cd .
- cd ~
- cd path
- cd /path
- cd ~/path
- replace PWD in env
- replace OLDPWD in env but only if it is not the same dir.
#### export
- export "declare -x VAR=VAL"
- export bla=bla
- make sure variables can only start with a A or _
- Double check the value in env
- test existing var
- test new var
#### unset
- unset VAR
- should return 0 without arguments
- double check env
#### env
- should print environment variables in list
- with arguments "env: $ARG: No such file or directory"
#### pwd
- should print the working directory
- should ignore arguments
#### echo
- echo hallo
- echo "hallo"
- echo 'hallo'
- echo -n hallo
- echo -nnn hallo
- echo -nnm hallo
- echo -n -n hallo
#### exit
- exit should exit with 0
- exit 123 should exit with 123
- exit blabla should exit with a warning and code -1
#### alias
- should be easy, it is like unset so easy extra points :)
#### z
- might be a tough one, but certainly extremely handy

---
## Bugs
#### crashes when giving proper memory and a lot of arguments
#### Overwrites line when typing past the terminal width at first command
#### piping fails when echo is the first arg
---
## Extras
#### Handle scripts from stdin or argument (very handy for testing)
- Simply run the lines 1 by one trough the parser and executor and quit when done. so simply skip the prompt
- Functions() are probably too much
- Statements, if, then, else, elif, while, for are probably too much too.
#### Posix Compliant
- //// is the same as / or /////////////////////////////

---
### Cleanup
- No memory leaks found in any testcase
- Break up code into digestable functions
- Norminette

---
## Usage
1. Simply clone or download the repository
2. Run `make` in the cloned directory
3. Start the shell with `./minishell`

---
## Tester
- write seperate testfunction for redirections, cd, env, export and unset that checks a specific part of the output of env

---
[This project is part of the studies at 42](https://42.fr/en/homepage/)
