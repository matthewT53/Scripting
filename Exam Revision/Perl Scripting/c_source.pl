#!/usr/bin/perl -w

# check to see if the correct number of arguments is supplied
if ($#ARGV != 0){
	print "Incorrect number of arguments\n";
	exit 0;
}


$file_type = $ARGV[0];
$total = 0;
foreach $file (sort(glob("*.$file_type"))){
	open PERL_FILE, "<", $file or die "Unable to open file: $file";
	while (<PERL_FILE>) {}
	printf "%6d $file\n", $.;
	$total += $.;
	close PERL_FILE;
}
printf "%6d total\n", $total; 
