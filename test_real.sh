testsDir='real_tests'
echo $testsDir
resultsDir=$testsDir/results
echo $resultsDir
for testFile in $(find $testsDir -name *.arr); do
    filePath=$(echo $testFile | cut -d'.' -f1)
    fileName=$(echo $filePath | cut -d'/' -f2)
    echo $filePath $fileName
    ./codeGenerator < $testFile > ${filePath}.c
    echo $resultsDir
    gcc -o $resultsDir/${fileName}_result ${filePath}.c
    ./$resultsDir/${fileName}_result
done