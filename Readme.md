# Project Name
Minishell is a lightweight implementation of bash

---
## Todo
#### Environment
- Write new CWD to $CWD
- Parse ~/.mshrc
- write return code to $?
- SHLVL +1 at launch

#### Parser
1. Quotes
2. ```;```
3. ```{} () < > << >> <<< | [] ? & && ||```
4. ```* $NAME $(command)```
5. prepare command structs for execve

#### Exec
1. fork if there are pipes
2. execve all the command structs in current pipe struct

#### Builtins
- cd
	cd ..
	cd .
	cd /path
	cd path
	cd
	replace PWD in env
	replace OLDPWD in env but only if it is not the same dir.
- export
- unset
- alias
- env Test properly
- pwd Test properly
- echo Test properly
- exit Test properly

#### Signals
- ```^C``` should break the readline
- ```^\``` shouldn't print anything

---
## Bugs
#### crashes when giving proper memory and a lot of arguments
#### Overwrites line when typing past the terminal width at first command

---
## Improvements
#### Handle scripts from stdin or argument
- Functions()
- Statements, if, then, else, elif, while, for
#### Posix Compliant
- //// is the same as / or /////////////////////////////
#### Extra Builtins
- z to jump around


---
## Usage
1. Simply clone or download the repository
2. Run `make` in the cloned directory
3. Start the shell with `./minishell`

---
## Tester
### Todo
- Figure out the best way to test minishell

---
[This project is part of the studies at 42](https://42.fr/en/homepage/)
