#!/bin/bash

# 十分脑残的OI对拍脚本 v2.0
# 20170902 by limejuice
# 这个主要是评测用
# 请不要在代码中使用freopen()
# 退出时一定要return 0

TIME_LIMIT="1s"
MAXIMUM_WRONG_LINES=15
COMPILE_ARGS="-O2 -Wall -Wextra"
IN_SUFFIX=".in"
OUT_SUFFIX=".out"

if [ $# -ne 2 ]; then
    echo "Usage: $0 <input/output directory> <source file>"
    exit 1
fi
if [ ! -d $1 ]; then
    echo "Directory doesn't exist!"
    exit 1
fi
echo "Compiling source file..."
g++ "$2" -o "/tmp/prog" $COMPILE_ARGS
if [ $? -gt 0 ]; then
    echo "Compile error,aborting..."
    exit 1
fi

cnt=0
right=0
for f in `ls $1|grep $IN_SUFFIX` ;do
	f=`echo $f|sed "s/${IN_SUFFIX}//g"`
    [ -f ${1}/${f}${IN_SUFFIX} ] || continue
    [ -f ${1}/${f}${OUT_SUFFIX} ] || continue
    echo "Testing case ${f}:"
    timeout $TIME_LIMIT "/tmp/prog" < ${1}/${f}${IN_SUFFIX} > /tmp/out 2>&-
    ret=$?
    if [ $ret -eq 124 ]; then
        echo "Time limit exceeded."
    elif [ $ret -gt 0 ]; then
        echo "Runtime error."
    else
        diff -ZBbq "/tmp/out" "${1}/${f}${OUT_SUFFIX}" > /dev/null
        if [ $? -gt 0 ];then
            echo "Wrong answer:"
            diff -ZBby "/tmp/out" "${1}/${f}${OUT_SUFFIX}" | head -n $MAXIMUM_WRONG_LINES
        else
            echo "Accepted."
            right=$[right+1]
        fi
    fi
    cnt=$[cnt+1]
done
echo "Finished.Got a score ${right} out of ${cnt}."
rm -f /tmp/prog /tmp/out 2>&-
exit 0