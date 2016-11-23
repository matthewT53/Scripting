#!/bin/sh
n=5 # the number of digits to generate
# pre-defined test case
i=0
testInput=""
while test $i -lt $n
do
    testInput=$testInput$i"\n"
    i=`expr $i + 1`
done

printf "$testInput"

output=`printf "$testInput" | ./shuffle.pl | sort`
# sort chucks some random characters inside fucks shit up
output2=`printf "$testInput" | sort`

output="$output"
output2="$output2"
printf "$output\n"

if [ "$output" = "$output2" ];
then
    echo "Yay"
fi

printf "Experiment 2:\n"
i=0
permutations=""
while test $i -lt $n
do
    output=`printf "$testInput" | ./shuffle.pl`
    permutations="$permutations""$output\n"
    i=`expr $i + 1`
done

# try to extract one set of results
setOne=`printf "$permutations" | tail -n$n | sort`

printf "$permutations"

printf "First set:\n"
printf "$setOne\n"

output=`printf "$output" | sort`
if [ "$setOne" = "$output" ];
then
    echo "Excellent"
fi
