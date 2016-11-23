#!/usr/bin/perl -w

$max = 10;
if (@ARGV && $ARGV[0] =~ /-[0-9]+/){
    $max = -shift @ARGV;
#    shift: Pops off the front
#    pop: pops off the back
#    unshift: pushes to the front
#    push: pushes to the back
}

$i = 1;

$ARGV[0] = "-" if @ARGV == 0;
foreach $file (@ARGV){
    open INPUT, $file or die "Failed to open $file\n" # does first thing first and then does the 2nd if the 1st Failed
    print "====> $file <====\n";
    while (<INPUT>){
        last if ($i++ > $max);
        print;
    }
}
