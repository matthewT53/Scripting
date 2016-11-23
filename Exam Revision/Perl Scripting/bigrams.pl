#!/usr/bin/perl -w

# no arguments were supplied so use STDIN
if ($#ARGV == -1){
	@stream = <STDIN>;
}

# open each argument as a file
else{
	@stream = <>;
}

# loop through each line of the stream
foreach $line (@stream){
	$line =~ s/[^ \w]/ /g;
	@words = split /\s+/, $line;
	for ($i = 0; $i < $#words; $i++){
		$word1 = lc $words[$i];
		$word2 = lc $words[$i + 1];
		#print "Word1 = $word1 and Word2 = $word2\n";
		$word_frequency{$word1}++;
		$bigrams{$word1}{$word2}++;
	}

	# don't forget about the occurence of the last word in the line
	if (defined($word2)){
		#print "Adding extra for word: $word2\n";
		$word_frequency{$word2}++;
	}
}

# print the results
foreach $word1 (sort keys %bigrams){
	@word2_sorted = sort { $bigrams{$word1}{$a} <=> $bigrams{$word1}{$b} } keys %{ $bigrams{$word1} };
	$word2 = $word2_sorted[0];
	$word1_freq = $word_frequency{$word1};
	$word2_follows_word1 = $bigrams{$word1}{$word2};
	print "$word1($word1_freq) $word2($word2_follows_word1)\n";
}
