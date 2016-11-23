#!/usr/bin/perl -w

$hourlyFlag = 0;
$tableFlag = 0;
$order = 0; # order for the lecture times
$orderHour = 0; # order for the lecture hours

# offsets for webpage data
$lecTimes = 6;

# data structures to store the lecture data
%{hourlyOutputs} = ();
%{tableData} = ();

# extract all the arguments
for $arg(@ARGV){
	if ($arg eq "-d"){
		$hourlyFlag = 1;
	}

    elsif ($arg eq "-t"){
        $tableFlag = 1;
    }

	else{
		push @courses, $arg;
	}
}

foreach $course (@courses){
	$url = "http://timetable.unsw.edu.au/current/"."$course".".html";
	$webpage = `wget -q -O- '$url'`;
	@lectures = $webpage =~ /td class=\"data\">(.*)</g;

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
					if ($hourlyFlag || $tableFlag){
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

# determine which format to print in
if ($hourlyFlag){
	printHourly();
}

if ($tableFlag){
	printTables();
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

# print the above information in a table
sub printTables{
	foreach $semester (keys %tableData){
		printTableSemester($semester);
	}
}

sub printTableSemester{
	my ($semester) = $_[0];
	my @daysInWeek = ("Mon", "Tue", "Wed", "Thu", "Fri");
	my $startHour = 9;
	my $finishHour = 20;

	# print the top row
	printf "%-6s", $semester;
	foreach $day (@daysInWeek){
		printf "%6s", $day;
	}
	print "\n";

	# print all the other rows
	for ($currHour = $startHour; $currHour <= $finishHour; $currHour++){
		# print the starting hour in the first column
		if ($currHour =~ /^[0-9]$/){
			printf "%-5s", "0$currHour:00";
		}

		else{
			printf "%-5s", "$currHour:00";
		}

		# print the # of lectures that occur at a specific time
		foreach $day (@daysInWeek){
			if (defined($tableData{$semester}{$day}{$currHour})){
				printf "%6s", $tableData{$semester}{$day}{$currHour};
			}

			else{
				print " " x 6;
			}
		}
		print "\n";
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
							$tableData{$semCode}{$day}{$hourPrint}++; # same as above comment
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
