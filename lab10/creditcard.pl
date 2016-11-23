#!/usr/bin/perl -w
# validate a credit card number by calculating its
# checksum using Luhn's formula (https://en.wikipedia.org/wiki/Luhn_algorithm)

# read all the arguments
foreach $arg (@ARGV){
	print validate($arg);
}

sub validate{
	my ($credit_card) = @_;
	my $number = $credit_card;
	$number =~ s/\D//g;
	# print "Number = $number\n";
	my @numbers = split //, $number;
	if ($#numbers + 1 != 16){
		# print "Length = $#numbers\n";
		return $credit_card . " is invalid - does not contain exactly 16 digits\n";
	}

	elsif (luhn_checksum(@numbers) % 10 == 0){
		return $credit_card . " is valid\n";
	}

	else{
		return $credit_card . " is invalid\n";
	}
}

sub luhn_checksum{
	my (@number) = @_;
	my @digits = reverse @number;
	my $index = 0;
	my $checkSum = 0;
	foreach $digit (@digits){
		my $multiplier = (1 + $index++) % 2;
		my $d = $digit * $multiplier;
		if ($d > 9){
			$d -= 9;
		}
		$checkSum += $d;
	}
	
	return $checkSum;
}
