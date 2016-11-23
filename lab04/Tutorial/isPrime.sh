#!/bin/sh

if test $# -ne 1
then
    echo "Usage: $0 <number>"
    exit 1
fi
n=$1
i=2
while [ $i -lt $n ]
do
    if test `expr $n  % $i` -eq 0
    then
        echo "$ is not prime"
        exit 1
    fi
    i=`expr $i + 1`
done
echo "$n is prime"
exit 0
