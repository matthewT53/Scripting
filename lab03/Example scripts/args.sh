#!/bin/sh

# set -x debugging
if test $# -ne 2
then 
	echo "Usage: count.sh [start] [finish]"
	exit 1
fi

start=$1
finish=$2

i=$start

while test $i -le $finish
do
	echo $i
	i=`expr $i + 1`
	sleep 1
done
