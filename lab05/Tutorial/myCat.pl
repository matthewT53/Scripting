#!/usr/bin/perl -w

# false = null or 0
# true = anything other than 0

# code doesn't work for -nv or -n and -v

# last q in tutorial print reverse <>

if (@ARGV > 0 && $ARGV[0] eq "-n"){
    $doNumbering = 1;
    shift;
}

if (@ARGV > 0 && $ARGV[0] eq "-v"){
    $doVisible = 1;
    shift;
}

$nLines = 1;
while (<>){
    printf "%6d ", $nLines++ if $doNumbering;
    if (!$doVisible){
        print;
    }

    else{
        chomp;
        foreach $c (split //) {
            if (ord($c) >= 32){ # returns the int rep of a character
                print "$c"
            }

            else{
                print "^".chr(ord($c) + 64);
            }
        }
        prnt "\$\n"
    }
}
