#!/usr/bin/perl -w

# helpful links:
# * http://perldoc.perl.org/perlreftut.html

# function prototype
sub reduce(&@);

$sum = reduce { $a + $b } 1 .. 10;
$min = reduce { $a < $b ? $a : $b } 5..10;
$maxstr = reduce { $a gt $b ? $a : $b } 'aa'..'ee';
$concat = reduce { $a . $b } 'J'..'P';
$sep = '-';
$join = reduce { "$a$sep$b" }  'A'..'E';
print "$sum $min $maxstr $concat $join\n";

sub reduce(&@){
	my ($func, @array) = @_;
	# array is empty
	if ($#array == -1){
		return undef;
	}

	# array has only one element, used as the base case
	elsif ($#array == 0){
		return $array[0];
	}

	# every other case
	else{
		# set the 1st and 2nd elements for the first call
		$a = shift @array;
		$b = shift @array;

		# calculate sum for first call with 1st and 2nd elements set
		$a = &$func;

		# run through all the numbers in the array
		foreach $b (@array){
			# do the subsequent calls
			$a = &$func;
		}

		return $a;
	}
}

