#!/usr/bin/perl -w
$debug = 0;
foreach $arg (@ARGV){
	if ($arg eq "-d"){ # enable debugging
		$debug = 1;
	}

	else{
		push @files, $arg; # add argument ot the list of files to open
	}
}

# loop through all the words in the poem
foreach $poem (@files){
	foreach $file (glob "poems/*.txt"){ # $file = $author
		open P, "<$poem" or die "Unable to open poem file.\n";
		# extract the author from the filename
		$author = $file;
		$author =~ s/poems\///g;
		$author =~ s/\.txt//g;
		$author =~ s/_/ /g;
		# traverse through each line of the input poem
		while ($line = <P>){
			@words = split /[^a-zA-Z]/, $line;
			# traverse through each word of the input poem
			foreach $word (@words){
				# find the log prob of the word in the Poet's poem
				if ($word ne ""){
					$logProbability = logProb($file, $word);
					# print "Added $logProbability to hash table.\n";
					if (defined($logSums{$poem}{$author})){
						# print "Defined value is: $logSums{$poem}{$file}\n";
						$logSums{$poem}{$author} += $logProbability;
					}

					else{
						# print "Assigned a new hash value.\n";
						$logSums{$poem}{$author} = $logProbability;
					}
				}
			}
		}

		if ($debug == 1){
			printf "%s: log_probability of %.1f for %s\n", $poem, $logSums{$poem}{$author}, $author;
		}

		close(P);
	}
}

foreach my $poem (sort keys %logSums){
	# swap a and b around for ascending vs descending
	@allKeys = sort { $logSums{$poem}{$b} <=> $logSums{$poem}{$a} } keys %{$logSums{$poem}};
	$author = $allKeys[0];
	printf "%s most resembles the work of %s (log-probability=%.1f)\n", $poem, $author, $logSums{$poem}{$author};
}

# calculates the log probability of a word in a file
sub logProb{
	my $file = $_[0];
	my $wordToSearch = $_[1];
	my $totalWords = findTotalWords($file);
	my $wordsMatched = findTotalMatches($file, $wordToSearch);
	my $frequency = ($wordsMatched + 1) / $totalWords;
	my $logResult = log($frequency);
	return $logResult;
}

# finds the total number of words in a file
sub findTotalWords{
	my $file = $_[0]; # get the filename from the argument list
	my $total = 0;
	open F, "<$file" or die "Failed to open file\n";
	while ($line = <F>){
		my @words = split /[^a-zA-Z]/, $line;
		foreach $word (@words){
			if ($word ne ""){
				$total++;
			}
		}
	}
	close(F);
	return $total;
	#print "$total words\n";
}

# finds how many times a certain word occurs in a file
sub findTotalMatches{
	my $wordToSearch = lc($_[1]); # get the word from the commandline
	my $filename = $_[0];
	my $total = 0;
	open F, "<$filename" or die "Failed to open file for testing\n";
	while ($line = <F>){
		my @words = split /[^a-zA-Z]/, $line;
		foreach $word (@words){
			if (lc($word) eq $wordToSearch){ # the word was found
				$total++;
			}
		}
	}
	close(F);
	return $total;
}
