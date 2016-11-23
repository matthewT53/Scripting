#!/usr/bin/perl -w

$last_line ="";
while ($line = <STDIN>){
    chomp $line;
    if ($line eq $last_line){
        print "Snap!!!!\n"
    }
    $last_line = $line;
}
