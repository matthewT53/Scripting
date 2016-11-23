#!/usr/bin/perl -w

# determine if the correct number of arguments was given
if ($#ARGV+1 != 2){
	print "Usage: ./echon.pl <number of lines> <string> at ./echon.pl line 3.", "\n";
	exit(1);
}

$max = $ARGV[0];
$string = $ARGV[1];
# check to see if second arg is actually a number
if ($max =~ /[^0-9]/){
	print "Usage: ./echon.pl <number of lines> <string> at ./echon.pl line 3.", "\n";
	exit(1);
}

$i = 0;
while ($i < $max){
	print $string, "\n";
	$i = $i + 1;
}
