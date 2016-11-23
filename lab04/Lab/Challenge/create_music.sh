#!/bin/sh

# pipe with hexdump -C to see the hex-rep of the non-printing bytes
if test $# -ne 2
then
    echo "Usage: ./create_music.sh <sample mp3> <directory to create>"
fi

webpage=`wget -q -O- 'https://en.wikipedia.org/wiki/Triple_J_Hottest_100?action=raw'`
sampleMP3=$1
dirToCreate=$2

temp=$samepleMp3".tmp.$$" # use ls -a to see the temp files

# create a temporary mp3 file to avoid modifying the original
cp "$sampleMP3" "$temp"

mkdir "$dirToCreate"
startYear=1993
endYear=2015

while test $startYear -le $endYear
do
    echo "$startYear :"
    tracksRaw=`echo "$webpage" | egrep -A11 "$startYear\|$startYear]]" | egrep "^#"`
    # the code below is required to remove all useless characters such as [ or ] as well as to remove non-ascii characters such as
    tracksCleaned=`echo "$tracksRaw" | sed "s/\[\[//g" | sed "s/\]\]//g" | sed "s/\"//g" | sed "s/^# //g" | sed "s/\xe2\x80\x93/-/g;s/\//-/g" | sed "s/#//g"`
    trackNum=1
    # echo "$tracksCleaned"
    # create a directory to store all the top hits for the year
    dirForTracks="$dirToCreate""/Triple J Hottest 100, ""$startYear"
    mkdir "$dirForTracks"
    while test $trackNum -le 10
    do
        # extract artist and title of song
        track=`echo "$tracksCleaned" | head -n$trackNum | tail -n1`
        echo "$track"
        artist=`echo "$track" | awk -F ' - ' '{print $1}'`
        title=`echo "$track" | awk -F ' - ' '{print $2}'`

        # check both artist and title for the OR condition
        # found an OR operation in artist
        if echo "$artist" | egrep "\|" > /dev/null
        then
            # need to see if there is more than 1 artist i.e "featuring"
            artistLeft=`echo "$artist" | cut -d'|' -f1`
            artistRight=`echo "$artist" | cut -d'|' -f2`
            if echo "$artistLeft" | egrep "featuring|Featuring" > /dev/null
            then
                artist="$artistLeft"
            else
                artist="$artistRight"
            fi
        fi

        # found an OR operation in title
        if echo "$title" | egrep "\|" > /dev/null
        then
            title=`echo "$title" | cut -d'|' -f2`
        fi
        echo "Artist: $artist"
        echo "Title: $title"

        # rename the sample mp3 then copy it to the directory created above
        filename="$trackNum"" - ""$title"" - ""$artist"".mp3"
        cp "$temp" "$filename"
        mv "$filename" "$dirForTracks"

        trackNum=`expr $trackNum + 1`
    done
    startYear=`expr $startYear + 1`
done
