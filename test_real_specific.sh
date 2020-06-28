testsDir='real_tests'
resultsDir=$testsDir/results
filePath=$(echo $1 | cut -d'.' -f1)
fileName=$(echo $filePath | cut -d'/' -f2)
echo "Compilando ${fileName}..."
./codeGenerator < $1 > ${filePath}.c
if [ $? -eq 0 ]; then 
    gcc -o $resultsDir/${fileName}_result ${filePath}.c
    if [ $? -eq 0 ]; then 
        ./$resultsDir/${fileName}_result
    fi
fi
