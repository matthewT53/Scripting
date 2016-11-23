#!/usr/bin/perl -w

$i = 0;
while ($line = <STDIN>){
    $array[$i] = $line;
    $i++;
}

print "$i lines read, which are in reverse: \n";
$j = $#array; # last valid index of the array
while ($j >= 0){
    print "$array[$j]";
    $j--;
}

print "@array"; // prints the whole array
