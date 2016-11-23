#!/bin/sh
small=""
medium=""
large=""
for file in *
do
	lineCount=`wc -l $file | cut -d' ' -f1`
	#echo $lineCount
	if test $lineCount -lt 10
	then 
		small=$small" "$file
	elif test $lineCount -lt 100
	then
		medium=$medium" "$file
	else
		large=$large" "$file
	fi
done
echo "Small files:" $small
echo "Medium-sized files:" $medium
echo "Large files:" $large
