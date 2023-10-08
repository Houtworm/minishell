# Minishell
is a lightweight implementation of bash

---
## Todo
### Tester
- we should add a lot of bad syntax to make sure we won't segfault during evaluation.
### Environment
- Writing all temporary files to a folder in /tmp/ so we can easily remove the folder afterwards for clean execution.
### Parser
- redirection has some issues with quotes;
- Syntax checking can be improved a lot
- globbing should be moved to before redirection parsing because echo hallo > * should work.
- globbing is removing quotes...
- heredoc should parse all but only input the last heredoc file
- just a $ is hanging the shell
### Exec
- somehow terminate a foreground process if the next command says it had enough example: ```cat /dev/random | head -n 100```
- cat | cat | cat | ls // should exit when enter is pressed 3 times // same issue?
### Builtins
#### cd
- cd is not really changing directory
- cd - is having issues if oldpwd is not set.
- if getcwd fails we can get strange behavior, lets say we delete the parent directory
#### env
- shlvl in env is not updated right away?
#### alias
- is already implemented and used during init, it just can't be called from the shell yet

---
### Cleanup
- Check for forbidden functions
- look for optimizations anywhere in the code
- No memory leaks found in any testcase
- Break up code into digestable functions
- Norminette
- Push to 42 git
- double check
- close project
- evaluation

---
## Features
#### Mandatory
- ```CTRL + C```
- ```CTRL + \```
- ```CTRL + D```
- ```Handle History```
- ```parsing |```
- ```parsing >```
- ```parsing >>```
- ```parsing <```
- ```parsing <<```
- ```parsing ""```
- ```parsing ''```
- ```parsing $VAR```
- ```echo builtin```
- ```env builtin```
- ```pwd builtin```
- ```cd builtin```
- ```export builtin```
- ```unset builtin```
- ```exit builtin```
#### Bonus
- ```parsing &&```
- ```parsing ||```
- ```parsing ()```
- ```parsing *```
#### Extra
- ```kernel username and hostname in prompt```
- ```working directory in prompt```
- ```execution time in prompt```
- ```return code in prompt```
- ```History file```
- ```Unique history```
- ```Match history```
- ```-d debug mode```
- ```-c command argument```
- ```multi redirection a la ZSH```
- ```Handle SHLVL```
- ```handle script as argument```
- ```handling non closed quotes```
- ```handling non complete lines```
- ```insults you with syntax errors```
- ```points to syntax errors on line```
- ```parsing ~/.mshrc```
- ```parsing $()```
- ```parsing `` ```
- ```parsing ;```
- ```parsing ?```
- ```parsing ~```
- ```parsing []```
- ```parsing #```
- ```parsing $$```
- ```parsing !!```
- ```. builtin```
- ```alias builtin```
- ```z builtin with unique directory and advanced search```
- ```which builtin```
- ```exec builtin```

---
## Usage
1. Simply clone or download the repository
2. Run `make` in the cloned directory
3. Start the shell with `./minishell`

    You will need the GNU readline library installed on your system

---
[This project is part of the studies at 42](https://42.fr/en/homepage/)
