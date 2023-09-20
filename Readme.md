# Minishell
is a lightweight implementation of bash

---
## Todo
#### Environment
```^C``` should print ^C and restart the mainloop
```^\``` shouldn't print anything
```^D``` should quit the shell if line is empty
```^Z``` should suspend running application
Writing all temporary files to a folder in /tmp/ so we can easily remove the folder afterwards for clean execution.

#### Parser
ft_closequote should be expanded to ft_closeline including ' " ` and (
if the pipeline ends with || && or | we should probably we should call ft_completeline right after ft_closeline
$$ should translate to PID of shell
maybe add a count to ft_checkoutquote so functions using it don't have to loop to end of pipeline
Syntax checking can be improved a lot we need an exemption for < as it can be the first symbol on a new cmd line
globbing should be moved to before redirection parsing because echo hallo > * should work.
globbing is removing quotes...
globbing has some errors like ```ls ../*/*r*/b*i*```
after wildcards are working 100%, we can expand into ? and []
quotes in quotes have some issues here and there
heredoc should not print "minishell heredoc>" if there is input waiting already

#### Exec
forks should not run if there is a mismatching condition before in the pipeline
somehow terminate a foreground process if the next command says it had enough example: ```cat /dev/random | head -n 100```
return codes are not always working correctly.
push & to the background
if the output is redirected it shouldn't be passed to a pipe too. probably an easy if else statement in the dupmachine

### Builtins
#### cd
```cd - is having issues if oldpwd is not set.```
if getcwd fails we can get strange behavior, lets say we delete the parent directory
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
z could be improved by only storing unique directories
z can also be improved by focussing on the lowest directory as/in/thisone and only match the whole path if nothing is found.

---
## Bugs
#### crashes when giving proper memory and a lot of arguments
#### crashes when giving a very very long pipeline
#### Overwrites line when typing past the terminal width at first command // maybe just write that it can't find or parsed ~/.mshrc ?
#### cat | cat | cat | ls // should exit when enter is pressed 3 times
#### Test the signals from prompt and from cat
---
## Extras
//// is the same as / or /////////////////////////////
Make the -c command read multiple lines so the tester will work with those
builtins, which, jobs, fg, exec

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
