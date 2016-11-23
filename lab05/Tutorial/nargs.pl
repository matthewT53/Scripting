#!/usr/bin/perl -w

print $#ARGV + 1, "\n";
print @ARGV, "\n";

while ($line = <>){ # taking a line from the input
    $line =~ s/[aeiou]//gi;
    print $line;
}

while (<>){ # <STDIN>
    s/[aeiou]//gi;
    print;
}
