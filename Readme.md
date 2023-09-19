# Minishell
is a lightweight implementation of bash

---
## Todo
#### Environment
- ```^C``` should print ^C and restart the mainloop
- ```^\``` shouldn't print anything
- ```^D``` should quit the shell if line is empty
- ```^Z``` should suspend running application

#### Parser
globbing should be moved to before redirection parsing because echo hallo > * should work.
globbing is removing quotes...
globbing has some errors like ```ls ../*/*r*/b*i*```
after wildcards are working 100%, we can expand into ? and []
quotes in quotes have some issues here and there

#### Exec
somehow terminate a foreground process if the next command says it had enough example: ```cat /dev/random | head -n 100```
return codes are not always working correctly.

### Builtins
#### cd
```cd - is having issues if oldpwd is not set.```
#### export
make sure variables can only start with a A or _
somehow it is adding empty lines to env file.
#### env
with arguments it should print an error.
#### exit
- exit 123 should exit with 123
- exit blabla should exit with a warning and code -1
#### alias
is already implemented and used during init, it just can't be called from the shell yet
#### z
would be very cool to implement this, we just need to store every dir in a file in chdir.c or something
then when z is called just cd to the first match :)

---
## Bugs
#### crashes when giving proper memory and a lot of arguments
#### Overwrites line when typing past the terminal width at first command
#### cat | cat | cat | ls // should exit when enter is pressed 3 times
#### Test the signals from prompt and from cat
---
## Extras
//// is the same as / or /////////////////////////////

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
## Usage
1. Simply clone or download the repository
2. Run `make` in the cloned directory
3. Start the shell with `./minishell`

---
[This project is part of the studies at 42](https://42.fr/en/homepage/)
