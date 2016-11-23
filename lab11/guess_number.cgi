#!/usr/bin/perl -w

use CGI qw/:all/;
use CGI::Carp qw(fatalsToBrowser warningsToBrowser);

# Simple CGI script written by andrewt@cse.unsw.edu.au
# Outputs a form which will rerun the script
# An input field of type hidden is used to pass an integer
# to successive invocations


$max_number_to_guess = 99;

print <<eof;
Content-Type: text/html

<!DOCTYPE html>
<html lang="en">
<head>
	<link rel="stylesheet" type="text/css" href="guess_number.css">
    <title>Guess A Number</title>
</head>
<body>
eof

warningsToBrowser(1);

$number_to_guess = param('number_to_guess');
$guess = param('guess');

$game_over = 0;
$response = "";

if (defined $number_to_guess and defined $guess) {
    $guess =~ s/\D//g;
    $number_to_guess =~ s/\D//g;
    if ($guess == $number_to_guess) {
        $response = "You guessed right, it was $number_to_guess.\n";
        $game_over = 1;
    } elsif ($guess < $number_to_guess) {
        $response = "Its higher than $guess.\n";
    } else {
        $response = "Its lower than $guess.\n";
    }
} else {
    $number_to_guess = 1 + int(rand $max_number_to_guess);
    $response = "I've  thought of number 0..$max_number_to_guess\n";
}

print <<eof;
	<div class="game_response">
		$response
	</div>
eof

if ($game_over) {
print <<eof;
    <form method="POST" action="">
        <input type="submit" value="Play Again" class="textfield_win">
    </form>
eof
} else {
print <<eof;
    <form method="POST" action="">
        <input type="textfield" name="guess" class="textfield_tryagain">
        <input type="hidden" name="number_to_guess" value="$number_to_guess">
    </form>
eof
}

print <<eof;
</body>
</html>
eof
