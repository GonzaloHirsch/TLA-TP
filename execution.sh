if [ "$#" -ne 1 ]; then
    echo 'No file entered'
else 
rm -f ./tests/compiledCode.c
touch ./tests/compileCode.c
chmod 777 ./tests/compileCode.c
./codeGenerator < $1 > ./tests/compileCode.c
gcc ./tests/compileCode.c
./a.out
fi