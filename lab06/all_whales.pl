#!/usr/bin/perl -w

# get data from STDIN
while ($line = <STDIN>){
	if ($line =~ /(\d+)\s*(.+)$/){
		$species = $2;
		$individuals = $1;
		$species =~ s/([A-Z]*)/lc($1)/ge; # upper => lower case conversion
		$species =~ s/s$//g; # remove plurals
		$species =~ s/\s+/ /g; # remove middle spaces
		$species =~ s/\s+$//g; # remove trailing spaces
		
		# check if a value for num pods has been set
		if (defined($whalePods{$species})){
			$numPods = $whalePods{$species};
			$numPods++;
			$whalePods{$species} = $numPods; 
		}

		else{
			$whalePods{$species} = 1;
		}

		# check if a value for num individuals has been set
		if (defined($whaleIndividuals{$species})){
			$numIndividuals = $whaleIndividuals{$species};
			$numIndividuals += $individuals;
			$whaleIndividuals{$species} = $numIndividuals;
		}

		else{
			$whaleIndividuals{$species} = $individuals;
		}
	}
}

# print out all the information about whales
# $size = scalar keys %whalePods; # sizeof(whalePods) should be == sizeof(whaleIndividuals)

# sort the whale names in alphabetical order
for $whale (sort keys %whalePods){
	$numPods = $whalePods{$whale};
	$numIndividuals = $whaleIndividuals{$whale};
	print "$whale observations:  $numPods pods, $numIndividuals individuals\n";
}
		
