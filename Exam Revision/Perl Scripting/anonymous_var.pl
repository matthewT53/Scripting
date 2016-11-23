#!/usr/bin/perl -w
# Studying anonymous variables for COMP2041 exam

while (<>){
    if (/\d+/){
        print;
    }

    else{
        print "Looking for a number\n";
    }
}

@basket = ('apples', 'oranges', 'pears');
foreach (@basket){
    print;
    print "\n";
}
