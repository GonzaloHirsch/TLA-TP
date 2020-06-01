if [ $1 -n ]; then
    echo 'Nothing'
else 
rm fifo
mkfifo fifo
cat $1 > fifo &
gdb ./codeGenerator -q
fi