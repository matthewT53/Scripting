#!/usr/bin/perl -w

use LWP::Simple;

$courseCode = $ARGV[0];
$url = "http://www.timetable.unsw.edu.au/current/"."$courseCode"."KENS.html";
$webpage = `wget -q -O- '$url'`;
@courses = $webpage =~ />([a-zA-Z]{4}[0-9]{4})</g;
foreach $course (@courses){
	print "$course\n";
}

