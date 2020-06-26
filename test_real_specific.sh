testsDir='real_tests'
echo $testsDir
resultsDir=$testsDir/results
echo $resultsDir
filePath=$(echo $1 | cut -d'.' -f1)
fileName=$(echo $filePath | cut -d'/' -f2)
echo $filePath $fileName
./codeGenerator < $1 > ${filePath}.c
echo $resultsDir
gcc -o $resultsDir/${fileName}_result ${filePath}.c
./$resultsDir/${fileName}_result