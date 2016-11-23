#!/usr/bin/perl -w

$x = "Andrew";
$i = 0;
while ($i < 10){
    $x = $x.$x;
    print length $x, "\n";
    $i++;
}

# prints pow(2, 10) $x's
print $x, "\n"
