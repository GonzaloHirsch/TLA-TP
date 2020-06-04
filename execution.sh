if [ $1 -n ]; then
    echo 'No file entered'
else 
rm ./tests/compiledCode.c
touch ./tests/compileCode.c
chmod 777 ./tests/compileCode.c
./codeGenerator < $1 > ./tests/compileCode.c
gcc ./tests/compileCode.c
./a.out
fi