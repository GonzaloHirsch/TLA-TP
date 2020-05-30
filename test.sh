# for testFile in $(ls tests|grep -e '.*[^\.][^t][^s][^t]$'); do
#     echo $testFile
#     rm $testFile
# done

testsDir='tests'
echo $testsDir
resultsDir=$testsDir/results
echo $resultsDir
for testFile in $(find $testsDir -name *.tst); do
    filePath=$(echo $testFile | cut -d'.' -f1)
    fileName=$(echo $filePath | cut -d'/' -f2)
    echo $filePath $fileName
    ./codeGenerator < $testFile > ${filePath}.c
    echo $resultsDir
    # gcc -o $resultsDir/${fileName}_result ${filePath}.c
done