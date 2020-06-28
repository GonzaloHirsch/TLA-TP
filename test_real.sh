testsDir='real_tests'
resultsDir=$testsDir/results
mkdir ./$resultsDir
for testFile in $(find $testsDir -name *.arr); do
    filePath=$(echo $testFile | cut -d'.' -f1)
    fileName=$(echo $filePath | cut -d'/' -f2)
    echo "Compilando ${fileName}..."
    ./codeGenerator < $testFile > ${filePath}.c
    if [ $? -eq 0 ]; then 
        gcc -o $resultsDir/${fileName}_result ${filePath}.c
    fi
done