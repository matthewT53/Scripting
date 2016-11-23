#!/bin/sh
title=""
artist=""
album=""
year=""
track=""

for directory in "$@"
do
    files=`find "$directory" | egrep ".mp3$"`
    #printf "$files"
    i=1
    total=`echo "$files" | wc -l`
    while test $i -le $total
    do
        song=`echo "$files" | head -n$i | tail -n1`
        #echo "$song"
        #numDashes=`echo "$song" | sed "s/\(.\)/\1\n/g" | egrep "-" | wc -l`
        #numDashes=`expr $numDashes + 1`
        # extract the relevant details
        title=`echo "$song" | awk -F ' - ' '{print $2}'`
        artist=`echo "$song" | awk -F ' - ' '{print $3}' | sed "s/.mp3$//"`
        album=`echo "$song" | cut -d'/' -f2`
        year=`echo "$song" | cut -d',' -f2 | cut -d'/' -f1 | sed "s/ //"`
        track=`echo "$song" | cut -d'/' -f3 | cut -d' ' -f1`
        #echo "$title"
        #echo "$artist"
        #echo "$album"
        #echo "$year"
        #echo "$track"
        id3 "$song" -t "$title" > /dev/null
        id3 "$song" -T "$track" > /dev/null
        id3 "$song" -a "$artist" > /dev/null
        id3 "$song" -A "$album" > /dev/null
        id3 "$song" -y "$year" > /dev/null
        i=`expr $i + 1`
    done
done
