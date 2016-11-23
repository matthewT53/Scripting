#!/bin/sh
$i=1
while true #$i -lt $2
do
	echo $i
	i=`expr $i + 1`
	sleep 1
done
