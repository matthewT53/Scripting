#!/usr/bin/perl -w

$new_file = "$file.backup";

open NEWBOOK, ">$new_file" or die "$0 open '$new_file' failed: $!\n";

print NEWBOOK @array;

foreach $file (@ARGV){ # all the files given as cmd arguments

}
