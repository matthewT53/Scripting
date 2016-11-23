#!/usr/bin/perl -w

$max = 10;
if (@ARGV && $ARGV[0] =~ /-[0-9]+/){
    $max = -shift @ARGV;
}

$i = 1;
if (@ARGV == 0){
    @lines = <STDIN>;
    print @lines[0..$max-1];
    while ($1 = <STDIN>){
        if ($i++ > $max){
            last;
        }
        print $1;
    }
}

else{
    foreach $file (@ARGV){
        open INPUT, $file or die "Failed to open $file\n" # does first thing first and then does the 2nd if the 1st Failed
        print "====> $file <====\n";
        while (<INPUT>){
            last if ($i++ > $max);
            print;
        }
    }
}
