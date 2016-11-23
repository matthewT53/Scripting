#!/usr/bin/perl -w

my $regex = shift @ARGV;
while ($line = <>){
	if ($line =~ /$regex/){
		print "$line";
	}
}
