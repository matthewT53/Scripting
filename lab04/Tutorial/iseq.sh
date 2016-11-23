#!/bin/sh

case $# in
1) lo=1 hi=$1 inc=1;;
2) lo=$1 hi=$2 inc=1;;
3) lo=$1 hi=$3 inc=`expr $2-$1`;;
*) cat << EOF
Too many arguments
EOF
exit 1;;
esac

i=$lo
while [ $i -le $hi ]
do
    echo $i
    i=`expr $i + 1`
done
