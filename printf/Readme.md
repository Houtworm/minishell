# Printf
This project requires you to write your own Printf\
I have implemented these conversions
| Conversion | Description |
| ----------- | ----------- |
| % | prints percent sign |
| a | prints float in hexadecimal scientific notation |
| b | prints int in binary |
| c | prints char |
| d | prints decimal |
| e | prints float in various special ways |
| f | prints float |
| g | prints float in scientific notation |
| i | prints integer |
| n | prints number of bytes written at that point |
| o | prints unsigned integer |
| p | prints memory address |
| s | prints string |
| u | prints unsigned integer |
| x | prints int in lowercase hexadecimal |
| X | prints int in uppercase hexadecimal |

And these flags

| Flag | Description |
| -- | --- |
| # | Alternate Form |
| 0 | Zero Padding |
| - | Left Adjustment |
| space | Space before positive number |
| + | + before positive number |
| 1-9 | Field Width |
| . | Precision |
| * | variable placeholder |

---
## Todo
#### Implement %a correctly
#### Implement lenght modifiers Lqtjz

---
## Bugs
plus and space prints an extra space in rare undefined cases\
*floats lose precision*\
g printing 1.0000 while it should just print 1\
g giving the wrong return value in some cases\
e giving the wrong return value in some cases\
double check length modifiers "l" "ll" "h" "hh"\

---
## Usage
1. Simply clone or download the repository
2. Run `make` in the cloned directory
3. You can include the libftprintf.a in your own program

---
## Tester
#### Todo
- check for -Wall -Werror -Wextra
- Add Infinity and NAN tests
- Harder checking on %n
- check with 2 conversions 1 correct and the other wrong?
- add strings with variables without any arguments

#### Usage
1. Download test.sh and the tests folder to your printf directory
2. Make the file executable `chmod +x test.sh`
3. Run `./test.sh` to start the test

---
[This project is part of the studies at 42](https://42.fr/en/homepage/)
