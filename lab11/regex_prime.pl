#!/usr/bin/perl -w

# http://www.noulakaz.net/2007/03/18/a-regular-expression-to-check-for-prime-numbers/

$regex = /^1?$|^(11+?)\1+$/;
foreach $n (1..100) {
    $unary = 1 x $n;
    print "$n = $unary unary - ";
    if ($unary =~ /^1?$|^(11+?)\1+$/) {
        print "composite\n"
    } else {
        print "prime\n";
    }
}
