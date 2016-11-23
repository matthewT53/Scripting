#!/usr/bin/perl -w

$n = 0;
@lines = <STDIN>; # @ is used to denote arrays
$n = @lines; # get the number of lines
while ($line = <STDIN>){
    $chars += length $line; # can obmit brackets from function calls
    $n++;
}
print "$n lines $chars chars\n"
