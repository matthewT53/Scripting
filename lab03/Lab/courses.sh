#!/bin/sh
# no point checking number of arguments
if test $# -ne 1
then
    echo "Incorrect number of arguments: ./courses.sh <Course code>"
fi

# download the relevant webpages
underWebPage=`wget -q -O- "http://www.handbook.unsw.edu.au/vbook2016/brCoursesByAtoZ.jsp?StudyLevel=Undergraduate&descr=$1"`
postWebPage=`wget -q -O- "http://www.handbook.unsw.edu.au/vbook2016/brCoursesByAtoZ.jsp?StudyLevel=Postgraduate&descr=$1"`
courseNumbersU=`echo "$underWebPage"|egrep "(>$1[0-9]{4}<)"|cut -d'>' -f2|cut -d'<' -f1`
courseDescriptionU=`echo "$underWebPage"|egrep "$1" | egrep "<A href=" | cut -d'>' -f3 | cut -d'<' -f1`
courseNumbersP=`echo "$postWebPage"|egrep "(>$1[0-9]{4}<)"|cut -d'>' -f2|cut -d'<' -f1`
courseDescriptionP=`echo "$postWebPage"| egrep "$1" | egrep "<A href=" | cut -d'>' -f3 | cut -d'<' -f1`
# print the second item in the list
#dc=`echo "$courseDescriptionU"|tail -n2|head -n1`
#echo $dc

# combine the course codes of both the undergraduate and postgraduate courses
# combinedCourseNumbers=$courseNumbersU"\n"$courseNumbersP
# sortedCourseNumbers=`echo "$combinedCourseNumbers"|sort|uniq`

# sorting the descriptions is different
#echo "$sortedCourseNumbers"


#echo "$courseDescriptionU"
#count=`echo "$courseDescriptionU" | wc -l`
#echo "Count = " $count
#echo "Course selection:"
#courseDesc=`echo "$courseDescriptionU"|head -n3|tail -n1`
#echo "$courseDesc"

# Combine the undergraduate courses
allCourses=""
i=1
for courseNum in $courseNumbersU
do
    courseDesc=`echo "$courseDescriptionU"|head -n$i|tail -n1`
    allCourses=$allCourses$courseNum" "$courseDesc"\n"
    i=`expr $i + 1`
done

# Combine the post graduate courses
i=1
numLines=`echo "$courseNumbersP" | wc -l`
for courseNum in $courseNumbersP
do
    courseDesc=`echo "$courseDescriptionP"|head -n$i|tail -n1`
    allCourses=$allCourses$courseNum" "$courseDesc
    if test $i -ne $numLines
    then
        allCourses=$allCourses"\n"
    fi
    i=`expr $i + 1`
done

# remove duplicate courses that are both in the undergrad and postgrad
# when using cat -A sometimes the same thing are treated as different things
# some equivalent items have " $" and "$"
sortedAllCourses=`printf "$allCourses"| sed "s/ $//g"|sort -k1|uniq -c|sed "s/^ *[0-9]* //"`
printf "$sortedAllCourses\n"

# below shows how to traverse a list in shell
#combine the course number + space + course description
#for c in $courseDescriptionU
#do
#    echo $c
#done
