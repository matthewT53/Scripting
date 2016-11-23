#!/bin/sh
pngName=""
for file in *.jpg
do
	pngName=`echo $file | sed 's/.jpg$/.png/'`
	if [ -e $pngName ]
	then
		echo "$pngName already exists"
	else
		convert "$file" "$pngName"
		rm "$file"
	fi 
done

