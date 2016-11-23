#!/bin/sh

for file in "$@" `find "$@" -type f`
do
    temp="$file.tmp.$$"
    if [ -e $temp ]
    then
        echo "$temp" already exists
        exit 1
    fi
    sed 's/COMP2041/COMP2042/g;s/COMP9041/COMP9042/g' $file > $temp &&
    mv $temp $file
done

# && says if this succeeds then proceed
# $$ represents the process ID
