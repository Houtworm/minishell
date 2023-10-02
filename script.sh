echo Hello World!
printf "trunc seems to be working\n" > file
printf "appending too\n" >> file
echo "piping too" | cat >> file
cat file
