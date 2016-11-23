#!/usr/bin/perl -w
@numbers = ();

# get all the numbers from input
while ($line = <STDIN>){
	@integers_from_input = $line =~ /\s*(\d+)\s*/g;
	foreach $integer (@integers_from_input){
		push @numbers, $integer;
	}
}

# determine if the number sequence is converging
$is_converging = 1;

# less than two elements in the array
if ($#numbers < 1){
	print "Need at least two numbers\n";
}

elsif ($#numbers == 1){
	if ($numbers[1] > $numbers[0]){
		$is_converging = 0;
	}
}

else{
	# diff_lhs > diff_rhs for convergence to hold
	for ($i = 1; $i < $#numbers; $i++){
		$diff_lhs = $numbers[$i - 1] - $numbers[$i];
		$diff_rhs = $numbers[$i] - $numbers[$i + 1];
		if ($diff_lhs < $diff_rhs || $diff_lhs < 0 || $diff_rhs < 0){
			$is_converging = 0;
			last;
		} 
	}
}

if ($is_converging == 1){
	print "converging\n";
}

else{
	print "not converging\n";
}


