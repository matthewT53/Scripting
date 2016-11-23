#!/usr/bin/perl -w

$n = 0; # stores the number of lines
while ($line = <STDIN>){
    $lines[$n++] = $line;
}

# shuffle the data entered
$i = 0;
@numbersUsed = (0) x $n; # create an empty array
while ($i < $n){
    $randomNum = int(rand($n)); # take the floor function

    # check to see if the index generated is unique
    if ($numbersUsed[$randomNum] == 0){
        $numbersUsed[$randomNum] = 1;
        $shuffledContent[$randomNum] = $lines[$i];
        $i++;
    }
}

# print the shuffled content
foreach $line (@shuffledContent){
    print $line;
}
