#!/usr/bin/perl -w

if ($#ARGV != 0){
	print "Usage: ex3 course\n";
}

$course_code = $ARGV[0];

# loop through all the marks of each student
while ($line = <STDIN>){
	if ($line =~ /^\d{7}\s*([\w]{4}[\d]{4})\s*(\d{4})\s*(\w\d)\s*(\d+)/){
		$course = $1;
		$year = $2;
		$session = $3;
		$mark = $4;

		if ($course eq $course_code){
			$average{$year}{$session} += $mark;
			$occurences{$year}{$session} += 1;
		}
	}
}

# calculate the average
foreach $year (sort keys %average){
	foreach $session (sort keys %{ $average{$year} }){
		printf "%s %s %s %.1f\n", $year, $course_code, $session, ($average{$year}{$session} / $occurences{$year}{$session});
	}
}



