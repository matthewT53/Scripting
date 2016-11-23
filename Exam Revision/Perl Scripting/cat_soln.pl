#!/usr/bin/perl -w
if ($ARGV[0] eq "-n") {
    $doNumbering = 1; shift;
}
if ($ARGV[0] eq "-v") {
    $doVisible = 1; shift;
}
$nlines = 1;
while (<>) {
    printf "%6d  ",$nlines++ if ($doNumbering);
    if (!$doVisible) {
        print;
    }
    else {
        chomp;
        foreach $c (split //) {
            if (ord($c) >= 32) {
                print "$c";
            }
            else {
                print "^".chr(ord($c)+64);
            }
        }
        print "\$\n";
    }
}
