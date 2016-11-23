#!/usr/bin/perl -w
# Simple CGI script written by andrewt@cse.unsw.edu.au
# Outputs a form which will rerun the script
# An input field of type hidden is used to pass an integer
# to successive invocations

use CGI qw/:all/;
use CGI::Carp qw/fatalsToBrowser warningsToBrowser/;


print header, start_html("Credit Card Validation"), "\n";
warningsToBrowser(1);

print h2("Credit Card Validation"), "\n";

$startMessage = "Enter credit card number";
$credit_card = param("credit_card");
if (defined $credit_card) {
	# sanitize input, remove html tags
	$credit_card =~ s/\</&lt/g;
	$credit_card =~ s/\>/&gt/g;
	$credit_card =~ s/[\'\"]/mark/g;
    $message = validate($credit_card);
	if ($message =~ /invalid/){
		$message = "<b><span style=\"color: red\">$message</span></b>";
		$startMessage = "Try again";
	}	

	else{
		$message = "<p>$message</p>";
		$credit_card = "";
		$startMessage = "Another card number";
	}
}

else{
	$credit_card = "";
}

# store the html we want ot serve in a variable
$html = 
"This page checks whether a potential credit card number satisfies the Luhn Formula.<p></p>
<form>
$message
<p> $startMessage:
<input name=\"credit_card\" value=\"$credit_card\" type=\"text\"> 
<input name=\"submit\" value=\"Validate\" type=\"submit\"> 
<input name=\"Reset\" value=\"Reset\" type=\"reset\"> 
<input name=\"close\" value=\"Close\" type=\"submit\"> 
</p></form>";

# user clicked close so serve a different html
$close = param('close');
if (defined $close){
	$html = "Thank you for using the Credit Card Validator.";
}

print <<eof;
$html
eof

print end_html, "\n";
exit 0;

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
