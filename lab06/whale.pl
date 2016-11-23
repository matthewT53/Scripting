#!/usr/bin/perl -w

#print "$ARGV[0]";
#print "Number of arguments: $#ARGV + 1"

if (($#ARGV + 1) != 1){
	print "Usage: ./whale.pl <whale>";
	exit;
} 

$whaleType = $ARGV[0];
$individuals = 0;
$pods = 0;
while ($line = <STDIN>){
	if ($line =~ /(\d+)\s*(.+)$/){
		$species = $2;
		if ($species eq $whaleType){
			$pods++;
			$individuals += $1;
		}
	}	
}

print "$whaleType observations: $pods pods, $individuals individuals\n";
