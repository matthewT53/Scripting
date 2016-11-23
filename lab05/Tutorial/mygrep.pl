#!/usr/bin/perl -w

if ($ARGV[0] eq "-v"){
    $doOpposite = 1;
    shift @ARGV;
}

$pattern = shift @ARGV;

while (<>){
    if ($doOpposite){
        print if !/$pattern/;
    }

    else{
        print if /$pattern/;
    }
}

# if $line =~ /$pattern/;
