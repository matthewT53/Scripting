#!/usr/bin/perl -w

#$numArgs = $#ARGV + 1;
#if ($numArgs != 1){
#    print "Usage: ./prereq.pl <Course code>\n";
#}

$courseCode = $ARGV[0];
# print "Course code: $courseCode\n";

$urlPost = "http://www.handbook.unsw.edu.au/postgraduate/courses/2015/$courseCode.html";
$urlUnder = "http://www.handbook.unsw.edu.au/undergraduate/courses/2015/$courseCode.html";

# get all the pre-req courses
getPreReqs($urlUnder);
getPreReqs($urlPost);

# print the pre-reqs
for $course (sort keys %preReqCourses){
    print "$course\n";
}

# subroutine that extracts all the pre-req courses from a webpage
sub getPreReqs{
    # get the arguments passed to this function
    $url = $_[0];
    open F, "wget -q -O- $url|" or die;
    #open F, "webpage" or die;
    while ($line = <F>) {
        if ($line =~ /Pre: |Pre[Rr]equisite: |Pre[Rr]equisites?: |Pre-[Rr]equisite: |Pre-[Rr]equisites: /){
            #print "$line\n";
            $line =~ s/<\/p>.*//g;
            $line =~ s/^\s*<p>\w+: //g;
            #print "$line\n";
            my @temp = split / /, $line;
            #print "Another recursive call:\n";
            for $course (@temp){
                if ($course =~ /([A-Za-z]{4}[0-9]{4})/){
                    $course = $1;
                    $course = uc $course;
                    #print "$course\n";
                    $preReqCourses{$course} = 0;
                }
            }
            last;
        }
    }
    close F;
}
