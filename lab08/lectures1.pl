#!/usr/bin/perl -w

$hourlyFlag = 0;
$order = 0;
$lecTimes = 6;
$orderHour = 0; # order for the lecture hours

# data structures for storing lecture data
%{hourlyOutputs} = ();

# process the arguments
for $arg(@ARGV){
	if ($arg eq "-d"){
		$hourlyFlag = 1;
	}

	else{
		push @courses, $arg;
	}
}

# download lecture data for each course
foreach $course (@courses){
	$url = "http://timetable.unsw.edu.au/current/"."$course".".html";
	$webpage = `wget -q -O- '$url'`;
	@lectures = $webpage =~ /td class=\"data\">(.*)</g;
	$i = 0;

	# traverse through each line of the webpage
	for ($i = 0; $i < $#lectures - $lecTimes; $i++){
		$line = $lectures[$i];
		$webStream = $lectures[$i + 3];
		# If the lecture is a webstream, skip it
		if ($webStream !~ /WEB/g){
			# find a line the marks the start of the lecture information
			if ($line =~ />Lecture</g){
				$semesterRegex = $lectures[$i + 1];
				$semesterRegex =~ />([TU])([0-9])</g; # get the semester
				if ($1 eq 'U'){
					$semCode = "X"."$2";
				}

				else{
					$semCode = "S"."$2";
				}

				# extract the lecture times
				$lectureTimes = $lectures[$i + $lecTimes];
				$output = "$course: $semCode $lectureTimes";

				# check if the lecture time was previously recorded (avoid repeated outputs)
				if (!defined($lectureSchedule{$output})){
					# check if the user specified the "print hourly" flag
					if ($hourlyFlag){
						storeHourly($lectureTimes, $course, $semCode);
					}

					else{
						print "$output\n";
					}
					$lectureSchedule{$output} = $order++; # store it inside hash to prevent repeated outputs
				}
			}
		}
	}
}

if ($hourlyFlag){
	printHourly();
}

# print the times that the lectures start in hours
sub printHourly{
	# print "Inside another function call\n";
    my @sortedKeys = sort {$hourlyOutputs{$a} <=> $hourlyOutputs{$b}} keys %hourlyOutputs;
    # now print the data
    foreach my $lectureHour (@sortedKeys){
		print "$lectureHour\n";
    }
}

# store data in the two data structures mentioned above
sub storeHourly{
	# print "Storing lecture data.\n";
    my ($lectureTimes, $course, $semCode) = @_;
    #print "$times\n";
    my @times = split /,/, $lectureTimes;
    my $numLecturesWeek = 0;
    my $time = "";
    my @lectureDays;
    # loop through each part of the string
    foreach $time (@times){
        $time =~ s/^ //g; # remove prefixed-space character
        $time =~ s/\(.*//g; # remove everything in the brackets
        $time =~ s/.*\)//g; # above comment
        if ($time !~ /^$/){
            #print "$time\n";
            if ($time =~ /^[A-Z][a-z][a-z]$/){ # sometimes the lectures run on the same time for multiple days
                $lectureDays[$numLecturesWeek++] = $time;
                #print "counter = $numLecturesWeek\n";
                #print "Will repeat this.\n";
            }

            # extract the day and the times
            if ($time =~ /([A-Z][a-z][a-z])\s*(\d+):(\d+)\s*\-\s*(\d+):(\d+)\s*/){
                $lectureDays[$numLecturesWeek++] = $1;
                #print "counter = $numLecturesWeek\n";
                my $startHour = $2;
                my $startMin = $3;
                my $finishHour = $4;
                my $finishMin = $5;
                my $startTotal = $startHour*100 + $startMin;
                my $finishTotal = $finishHour*100 + $finishMin;
                #print "Day: $day\n";
                #print "startHour: $startHour\n";
                #print "startMin: $startMin\n";
                #print "finishHour: $finishHour\n";
                #print "finishMin: $finishMin\n";
                my $temp = $startTotal;
                for (my $i = 0; $i < $numLecturesWeek; $i++){
                    $startTotal = $temp;
                    while ($startTotal < $finishTotal){
                        my $hourPrint = $startTotal / 100;
                        my $day = $lectureDays[$i];
                        my $key = "$semCode $course $day $hourPrint";
						if (!defined($hourlyOutputs{$key})){
							#print "Key: $key Not already defined.\n";
                        	$hourlyOutputs{$key} = $orderHour++; # these refer to global variables
							#$tableData{$semCode}{$day}{$hourPrint}++; # same as above comment
						}
						# print "Sem code: $semCode\n";
                        $startTotal += 100;
                    }
                }

                $numLecturesWeek = 0; # reset the number of days the lecture runs on
                @lectureDays = (); # clear the array
            }
        }
    }
}
