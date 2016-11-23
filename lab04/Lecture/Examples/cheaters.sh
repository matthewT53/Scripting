#!/bin/sh
# cd /blah || exit # avoid deleting the whole of the curent directory

for file1 in "$@"
do
        for file2 in "$@"
        do
            sed 's/\/\/.*//
                s/".*"/string/g
                s/[_a-zA-Z][_a-zA-Z0-9]*/andrew/g
                ' $file1 > tmp1 # issue what if there is already a file called TMP1
            sed 's/\/\/.*//
                s/".*"/string/g
                 s/[_a-zA-Z][_a-zA-Z0-9]*/andrew/g
                 ' $file2 >tmp2
            src_lines=`wc -l tmp1`
            diff_lines=`diff tmp1 tmp2`
            percent_differences=$(((100*$diff_lines)/$src_lines))
            test "$file1" = "$file2" && continue
            if test $percent_differences -ge 20
            then
                echo $file1 $file2 may be the same work
            fi
        done
done
