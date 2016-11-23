#!/usr/bin/perl -w

# Associative array, hashes or dictionary
$array{"Andrew"} = "Rockets"; # note the curly brackets

print "$array{Andrew}\n";

while ($line = <>){
    $course = $line;
    $course =~ s/\|.*//;
    print "$course\n"
}
