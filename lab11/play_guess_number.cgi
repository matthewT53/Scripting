#!/usr/bin/perl -w

use CGI qw/:all/;
use CGI::Carp qw(fatalsToBrowser warningsToBrowser);
use POSIX;

# Simple CGI script written by andrewt@cse.unsw.edu.au
# Outputs a form which will rerun the script
# An input field of type hidden is used to pass an integer
# to successive invocations

$maxNum = 100;

print <<eof;
Content-Type: text/html

<!DOCTYPE html>
<html lang="en">
<head>
	<link rel="stylesheet" type="text/css" href="guess_number_browser.css">
    <title>Guess A Number</title>
</head>
<body>
eof

warningsToBrowser(1);
$maxNum = 100;

if (param('correct')){
print <<eof;
	<form method="POST" action="">
		I win!!!!
		<input type="submit" value="Play Again">
	</form>
eof
}

else{
	$low = param('low_limit');
	$high = param('high_limit');
	$m = floor(($low + $high) / 2);
	
	# higher button was pressed
	if (defined(param('higher'))){
		# change the lower limits
		$guess = floor((($m + 1) + $high) / 2);
		mainWindow($guess, $m + 1, $high);
	}

	# lower button was pressed
	elsif (defined(param('lower'))){
		# change the higher limits
		$guess = floor((($m - 1) + $low) / 2);
		mainWindow($guess, $low, $m - 1);
	}

	else{
		mainWindow(floor($maxNum / 2), 1, $maxNum);
	}
}

print <<eof;
</body>
</html>
eof

sub mainWindow{
	my ($my_guess, $my_low, $my_high) = @_;
print <<eof;
	<form method="POST" action="">
		My guess is: $my_guess
		<input name="higher" value="Higher?" type="submit"> 
		<input name="correct" value="Correct?" type="submit">
		<input name="lower" value="Lower?" type="submit">
		<input name="low_limit" value="$my_low" type="hidden"> 
		<input name="high_limit" value="$my_high" type="hidden"> 
		<input name="guess" value="$my_guess" type="hidden"> 
	</form>
eof
}
