echo Hello World!
printf "trunc seems to be working\n" > file
printf "appending too\n" >> file
echo "piping too" | cat >> file
cat file
echo and variables work too $USER
true && false || echo and conditions too
./minishell -c exit && echo launching programs too
echo -n command; echo -n end; echo too
echo "'"'quotes too'"'"
echo Goodbye World # This should not print
exit 69
