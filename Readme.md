# Minishell
is a lightweight implementation of bash

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
1. Split on pipes and create an extra pipe struct for every pipe
2. ignoring text inside quotes split on command end ```;```
3. ignoring text inside quotes split on & to know if it has to be pushed to the background.
4. ignoring text inside quotes split on && and || and assign the correct condition to the next command struct in pipe struct.
5. ignoring text inside quotes, expand variables like $VAR, *, ?, []
6. ignoring text inside quotes set the right fds and redirections for ```<, > and >>```
7. ignoring text inside quotes set the redirection to heredoc or herestring for ```<< and <<<```
8. ignoring text inside quotes check for $(command) and `command` and put it at the front of the command struct
9. finally get the absolute path for the main command and split the rest of the command on the space for execve

#### Exec
1. create a child for every pipe struct.
2. run the dupmachine, and set the redirect values heredoc or fd as the in and output.
3. execve the current command struct.
4. go to the next command in the struct and repeat steps 2 - 4 untill there are no commands left.
5. somehow terminate a foreground process if the next command says it had enough example: cat /dev/random | head -n 100
6. write return code to $?

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
- write seperate testfunction for cd, env, export and unset that checks a specific part of the output of env

---
[This project is part of the studies at 42](https://42.fr/en/homepage/)
