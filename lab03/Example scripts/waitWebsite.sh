#!/bin/sh

if test $# -ne 3
then
    echo "Incorrect number of arguments"
    echo "./waitWebsite <website> <regex> <emailaddr>"
fi

website=$1
regex=$2
emailAddr=$3
sleepTime=5

while true
do
    if curl $website | egrep -i $regex
    then
        echo "Taylor swift tickets are up!!!!!!!" | mail $emailAddr
        exit 0
    else
        echo -n .
    fi
    sleep 5
done
