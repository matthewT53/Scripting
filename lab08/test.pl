#!/usr/bin/perl -w
$line = "";
$line = <STDIN>;
@times = split /,/, $line;
foreach $time (@times){
    $time =~ s/^ //g;
    $time =~ s/\(.*//g;
    $time =~ s/.*\)//g;
    if ($time !~ /^$/){
        print "$time\n";
        #print "Printing time format:\n";
        if ($time =~ /([A-Z][a-z][a-z])\s*(\d+):(\d+)\s*\-\s*(\d+):(\d+)\s*/){
            $day = $1;
            $startHour = $2;
            $startMin = $3;
            $finishHour = $4;
            $finishMin = $5;
            print "Day: $day\n";
            print "startHour: $startHour\n";
            print "startMin: $startMin\n";
            print "finishHour: $finishHour\n";
            print "finishMin: $finishMin\n";
        }
    }
}
