#!/usr/bin/perl -w

$total = 0;
while ($line = <STDIN>){
	@words = split /[^a-zA-Z]/, $line;
	foreach $word (@words){
		if ($word ne ""){
			$total++;
		}
	}
}

print "$total words\n";
