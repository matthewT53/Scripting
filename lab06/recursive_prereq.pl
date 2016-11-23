#!/usr/bin/perl -w
$recursive = 0; # flag to indicate whether we should find pre-req courses recursively

for $argument (@ARGV){
    if ($argument eq "-r"){
        $recursive = 1;
    }

    if ($argument =~ /[A-Z]{4}[0-9]{4}/){
        $courseCode = $argument;
    }
}

#print "Recursive set: $recursive\n";
#print "Course code: $courseCode\n";

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
        if ($line =~ /Pre: |Pre[Rr]equisite: |Pre[Rr]equisites: |Pre-[Rr]equisite: |Pre-[Rr]equisites: /){
            #print "$line\n";
            $line =~ s/<\/p>.*//g;
            $line =~ s/^\s*<p>\w+: //g;
            #print "$line\n";
            my @temp = split / /, $line;
            #print "Another recursive call:\n";
            for $course (@temp){
                #print "Before if statement: $course\n";
                if ($course =~ /([A-Za-z]{4}[0-9]{4})/){
                    $course = $1;
                    $course = uc $course;
                    # print "$course\n";
                    $preReqCourses{$course} = 0;
                    if ($recursive == 1){
                        my $urlPost = "http://www.handbook.unsw.edu.au/postgraduate/courses/2015/$course.html";
                        my $urlUnder = "http://www.handbook.unsw.edu.au/undergraduate/courses/2015/$course.html";
                        getPreReqs($urlPost);
                        getPreReqs($urlUnder);
                    }
                }
            }
            last;
        }
    }
    close F;
}
