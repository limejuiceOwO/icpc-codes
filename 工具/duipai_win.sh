#!/bin/bash

COMPLIER_ARGS="-O2 -Wall -Wextra"

if [ $# != 3 ];then
	echo "Usage:$0 gen prog1 prog2"
	exit 1
fi

#g++ $COMPLIER_ARGS $1 -o /tmp/gen &&
g++ $COMPLIER_ARGS $2 -o /tmp/prog1 &&
g++ $COMPLIER_ARGS $3 -o /tmp/prog2

if [ $? -gt 0 ];then
	echo "Compile error."
	exit 1
fi
cnt=0
while true; do
	echo "Data #${cnt}:"
	#/tmp/gen > /tmp/data &&
	python2 $1 > /tmp/data &&
	/tmp/prog1 < /tmp/data > /tmp/out1 &&
	/tmp/prog2 < /tmp/data > /tmp/out2
	if [[ $? -gt 0 ]];then
		echo "Runtime error"
		cp /tmp/data $PWD/data.txt
		break
	fi
	diff -ZBbq /tmp/out1 /tmp/out2
	if [[ $? -gt 0 ]];then
		echo "different"
		diff -ZBb /tmp/out1 /tmp/out2 | tee $PWD/diff.txt
		cp /tmp/data $PWD/data.txt
		cp /tmp/out1 $PWD/out1.txt
		cp /tmp/out2 $PWD/out2.txt
		break
	else
		echo "same"
		cnt=$[cnt+1]
	fi
done