#!/usr/bin/perl -w
$order = 0;
foreach $arg (@ARGV){
	$url = "http://timetable.unsw.edu.au/current/"."$arg".".html";
	$webpage = `wget -q -O- '$url'`;
	@lectures = $webpage =~ /td class=\"data\">(.*)</g;
	$i = 0;

	for ($i = 0; $i < $#lectures - 6; $i++){
		$line = $lectures[$i];
		$webStream = $lectures[$i + 3];

		if ($webStream !~ /WEB/g){
			if ($line =~ />Lecture</g){
				$semesterRegex = $lectures[$i + 1];
				$semesterRegex =~ />([TU])([0-9])</g; # get the semester
				if ($1 eq 'U'){
					$semester = $2;
					$char = 'X';
				}

				else{
					$semester = $2;
					$char = 'S';
				}

				$times = $lectures[$i + 6];
				$output = "$arg: $char$semester $times";
				$lectureTimes{$output} = $order++; # store it inside hash to prevent repeated outputs
			}
		}
	}
}

@sortedKeys = sort {$lectureTimes{$a} <=> $lectureTimes{$b}} keys %lectureTimes;
foreach $output (@sortedKeys){
	print "$output\n";
}
