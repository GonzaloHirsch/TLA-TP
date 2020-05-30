for testFile in $(ls tests|grep -e '.*[^\.][^t][^s][^t]$'); do
    echo $testFile
    rm $testFile
done
for testFile in $(find tests -name *.tst); do
    fileName=$(echo $testFile | cut -d'.' -f1)
    ./codeGenerator < $testFile > ${fileName}_result && gcc -o ${fileName}_result ${fileName}.c 
done