#!/usr/bin/perk -w
$n = 0;
@lines = <STDIN>;
$n = @lines;
$i = 0;
while ($i < @lines){
    $chars += length $lines[$i];
    $i++;
}

foreach $line (@lines){
    $chars += length $line;
}

$chars = length join("", "@lines"); # interprets the actual elements only for double quotes
print "$n lines $chars\n";
