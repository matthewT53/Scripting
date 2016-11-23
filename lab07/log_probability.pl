#!/usr/bin/perl -w

$wordToSearch = $ARGV[0];

foreach $file (glob "poems/*.txt"){
	$totalWords = findTotalWords($file);
	$wordsMatched = findTotalMatches($file, $wordToSearch);
	$frequency = ($wordsMatched + 1) / $totalWords;
	$logResult = log($frequency);
	$file =~ s/poems\///; # remove the directory
	$file =~ s/_/ /g;
	$file =~ s/\.txt//g;
	printf "log((%d+1)/%6d) = %8.4f %s\n", $wordsMatched, $totalWords, $logResult, $file;
}

# definition of sub functions here

sub findTotalWords{
	my $file = $_[0]; # get the filename from the argument list
	my $total = 0;
	open F, "$file" or die "Failed to open file\n";
	while ($line = <F>){
		my @words = split /[^a-zA-Z]/, $line;
		foreach $word (@words){
			if ($word ne ""){
				$total++;
			}
		}
	}

	return $total;
	#print "$total words\n";
}

sub findTotalMatches{
	my $wordToSearch = lc($_[1]); # get the word from the commandline
	my $filename = $_[0];
	my $total = 0;
	open F, "$filename" or die "Failed to open file for testing\n";
	while ($line = <F>){
		my @words = split /[^a-zA-Z]/, $line;
		foreach $word (@words){
			if (lc($word) eq $wordToSearch){ # the word was found
				$total++;
			}
		}
	}

	return $total;
}
