#!/bin/sh

for file in $@
do
	date=`ls -l "$file"|cut -d' ' -f6-9`
	convert -gravity south -pointsize 26 -draw "text 0,10'$date'" $file "$file.tmp$$"
    rm "$file"
	mv "$file.tmp$$" "$file" 
	touch -d"$date" "$file"
	display "$file"
done
