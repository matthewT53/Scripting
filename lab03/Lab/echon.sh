#!/bin/sh
if test $# -ne 2
then 
	echo "Usage: ./echon.sh <number of lines> <string>"
	exit 1
fi

arg1=$1
arg2=$2
number='^[0-9]+$'
if ! [[ $arg1 =~ $number ]];
then
	echo "./echon.sh: argument 1 must be a non-negative integer"
	exit 2
fi

i=0
while test $i -lt $arg1
do
	echo $arg2
	i=`expr $i + 1`
done
