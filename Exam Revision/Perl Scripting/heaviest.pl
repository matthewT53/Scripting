#!/usr/bin/perl -w

foreach $number (@ARGV){
	$weights{$number}++;
}

@sorted_keys = sort { $weights{$b} * $b <=> $weights{$a} * $a } keys %weights;
$heaviest_number = $sorted_keys[0];
print "$heaviest_number\n";
