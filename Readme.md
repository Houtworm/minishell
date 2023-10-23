# Minishell
---
## Todo
### Parsing
- Heredoc should react to signals
- ~~ is instant crash
### Builtin
#### Period
- just a / should print is a directory
### Tester
- we should add a lot of bad syntax to make sure we won't segfault during evaluation.

---
### Cleanup
- Check for forbidden functions
- look for optimizations anywhere in the code
- No memory leaks found in any testcase
- protect all mallocs
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
