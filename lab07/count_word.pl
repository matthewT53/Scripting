#!/usr/bin/perl -w

$wordToSearch = lc($ARGV[0]); # get the word from the commandline
$total = 0;
while ($line = <STDIN>){
	@words = split /[^a-zA-Z]/, $line;
	foreach $word (@words){
		if (lc($word) eq $wordToSearch){ # the word was found
			$total++;
		}
	}
}

print "$wordToSearch occurred $total times\n";
