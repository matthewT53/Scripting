#!/bin/sh

# basically my idea it to continously generate outputs and if an output is a unique permutation then store it
# each time an output is generated, check it against the permutations, if it doesn't exist then store in the list of permutations
# if an output is not a permutation then the program being tested is incorrect
# when the program terminates, the timing of execution can be an indicator to how random the program is

n=5 # the number of digits to generate
# pre-defined test case
testData=""
i=0
while test $i -lt $n
do
    testData="$testData""$i\n"
    i=`expr $i + 1`
done

# this makes it easier since sort chucks in a few invisible characters
defaultOutput=`printf "$testData" | sort`

# calculate permutation of n
i=1
perm=1
while test $i -le $n
do
    perm=`expr $perm \* $i`
    i=`expr $i + 1`
done

printf "$perm\n"

# test the pseudo random program
i=0 # keeps track of the # of permutations
permutations=""
failedTest=0
while test $i -lt $perm
do
    # boolean to determine whether the output should be added to a list
    addToList=1
    output=`printf "$testData" | ./shuffle.pl`
    validOutput=`printf "$output" | sort`
    # validOutput="fssdfsd" test to see what happens when output is not correct
    # determine if the output is a permutation
    if [ "$validOutput" = "$defaultOutput" ];
    then
        # check to see if this permutation already exists
        j=1
        while test $j -le $i # cycle through all the permutations
        do
            m=`expr $j \* $n`
            permOutput=`printf "$permutations" | head -n$m | tail -n$n`
            if [ "$permOutput" = "$output" ] # permutation already exists
            then
                addToList=0 # don't add to list of perms
                break;
            fi
            j=`expr $j + 1`
        done

        # if the output is correct and already in the list of permutations then add it in
        if test $addToList -eq 1
        then
            permutations="$permutations""$output\n"
            i=`expr $i + 1`
            # echo "$i adding Perm"
        fi
    else
        # output generated wasn't correct (not a permutation of the test data)
        echo "Error: Output generated is not a permutation of the test data"
        failedTest=1
        break;
    fi
done

# print a terminating message for the user
if test $failedTest -ne 1
then
    echo "You've done well sir!"
else
    echo "Test failed!"
fi
