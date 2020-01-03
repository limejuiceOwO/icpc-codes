#!/bin/bash

# 十分脑残的OI对拍脚本 v3.0
# 20170921 by limejuice
# 这个完全就是评测机了
# 请不要在代码中使用freopen()
# 退出时一定要return 0

TIME_LIMIT="1s"
MAXIMUM_WRONG_LINES=15
COMPILE_ARGS="-O2 -Wall -Wextra"
IN_SUFFIX=".in"
OUT_SUFFIX=".out"
SRC_SUFFIX=".cpp"

if [ $# -ne 2 ]; then
    echo "Usage: $0 <input/output directory> <source file/directory>"
    exit 1
fi
if [ ! -d $1 ]; then
    echo "I/O directory doesn't exist!"
    exit 1
fi

for src in `ls $2|grep $SRC_SUFFIX`; do
    echo "Compiling source file ${src} ..."
    [ -d $2 ] && src=${2}/${src}
    g++ "$src" -o "/tmp/prog" $COMPILE_ARGS
    if [ $? -gt 0 ]; then
        echo "Compile error"
        exit 1
    fi
    cnt=0
    right=0
    for f in `ls $1|grep $IN_SUFFIX` ;do
    	f=`echo $f|sed "s/${IN_SUFFIX}//g"`
        [ -f ${1}/${f}${IN_SUFFIX} ] || continue
        [ -f ${1}/${f}${OUT_SUFFIX} ] || continue
        echo "Testing case ${f} :"
        timeout $TIME_LIMIT "/tmp/prog" < ${1}/${f}${IN_SUFFIX} > /tmp/out 2>&-
        ret=$?
        if [ $ret -eq 124 ]; then
            echo "Time limit exceeded."
        elif [ $ret -gt 0 ]; then
            echo "Runtime error."
        else
            diff -ZBbq "/tmp/out" "${1}/${f}${OUT_SUFFIX}" > /dev/null
            if [ $? -gt 0 ];then
                echo "Wrong answer(yours|std):"
                diff -ZBby "/tmp/out" "${1}/${f}${OUT_SUFFIX}" | head -n $MAXIMUM_WRONG_LINES
            else
                echo "Accepted."
                right=$[right+1]
            fi
        fi
        cnt=$[cnt+1]
    done
    echo -e "Finished.Got a score ${right} out of ${cnt}.\n"
done

rm -f /tmp/prog /tmp/out 2>&-
echo "Everything is done."
exit 0