#!/bin/bash

# 十分脑残的OI对拍脚本 v1.0
# 20170202 by limejuice
# 请不要在代码中使用freopen()！

TIME_LIMIT="1s"
MAXIMUM_WRONG_LINES=15
COMPILE_ARGS="-O2 -Wall -Wextra"

if [ $# -ne 3 ]; then
    echo "Usage: $0 <input directory> <source file 1> <source file 2>"
    exit 1
fi
if [ ! -d $1 ]; then
    echo "Input directory doesn't exist!"
    exit 1
fi
echo "Compiling source files..."
g++ "$2" -o "/tmp/prog1" $COMPILE_ARGS && g++ "$3" -o "/tmp/prog2" $COMPILE_ARGS
if [ $? -gt 0 ]; then
    echo "Compile error,aborting..."
    exit 1
fi
for f in `ls $1` ;do
    [ -f ${1}/$f ] || continue
    echo "Testing case ${f}:"
    timeout $TIME_LIMIT "/tmp/prog1" < ${1}/$f > /tmp/out1 2>&- && timeout $TIME_LIMIT "/tmp/prog2" < ${1}/$f > /tmp/out2 2>&-
    ret=$?
    if [ $ret -eq 124 ]; then
        echo "Time limit exceeded."
    elif [ $ret -gt 0 ]; then
        echo "Runtime error."
    else
        diff -ZBbq "/tmp/out1" "/tmp/out2"
        if [ $? -gt 0 ];then
            echo "Wrong answer."
            diff -ZBby "/tmp/out1" "/tmp/out2" -W $MAXIMUM_WRONG_LINES
        else
            echo "Accepted."
        fi
    fi
done
echo "Finished."
rm -f /tmp/prog1 /tmp/prog2 /tmp/out1 /tmp/out2 2>&-
exit 0