# Minishell
is a lightweight implementation of bash

---
## Todo
#### Environment
- Writing all temporary files to a folder in /tmp/ so we can easily remove the folder afterwards for clean execution.

#### Parser
- split not quote is not null terminating properly? look in ft_chdir for an example
- maybe add a count to ft_checkoutquote so functions using it don't have to loop to end of pipeline
- Syntax checking can be improved a lot
- globbing should be moved to before redirection parsing because echo hallo > * should work.
- globbing is removing quotes...
- quotes in quotes have some issues here and there
- heredoc should not print "minishell heredoc>" if there is input waiting already
- heredoc should parse all but only input the last heredoc file

#### Exec
- forks should not run if there is a mismatching condition before in the pipeline
- somehow terminate a foreground process if the next command says it had enough example: ```cat /dev/random | head -n 100```
- push & to the background

### Builtins
#### cd
- cd - is having issues if oldpwd is not set.
- if getcwd fails we can get strange behavior, lets say we delete the parent directory
#### export
- make sure variables can only start with a A or _
- somehow it is adding empty lines to env file.
#### env
- if argument is a valid directory print permission denied, else print no such file or directory.
#### exit
- if argument is bigger than long long print numeric argument required
- huge numbers print the wrong return value
#### alias
- is already implemented and used during init, it just can't be called from the shell yet
#### .
- should handle files properly

---
## Bugs
#### crashes when giving proper memory and a lot of arguments
#### crashes when giving a very very long pipeline
#### Overwrites line when typing past the terminal width at first command // maybe just write that it can't find or parsed ~/.mshrc ?
#### cat | cat | cat | ls // should exit when enter is pressed 3 times
#### Test the signals from prompt and from cat
---
## Extras
- //// is the same as / or /////////////////////////////
- Make the -c command read multiple lines so the tester will work with those

---
### Cleanup
- look for optimizations anywhere in the code
- No memory leaks found in any testcase
- Break up code into digestable functions
- Norminette
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
- ```Unique line History file```
- ```-d debug mode```
- ```-c command argument```
- ```Handle SHLVL```
- ```handle script as argument```
- ```handling non closed quotes```
- ```handling non complete lines```
- ```insults you with syntax errors```
- ```points to syntax errors on line```
- ```parsing ~/.mshrc```
- ```parsing $(command)```
- ```parsing `command` ```
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
