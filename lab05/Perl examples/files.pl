#!/usr/bin/perl -w
# send error messages to standard error
$file = "myfile.txt";
if (!open HANDLE, $file){
    print STDERR "$0: Open '$file' failed: $!\n";
    die "$0: open '$file' failed: $!"; # prints the message then kills the program
    exit(1);
}

open BOOK, $file or die "$0: open dying message";
@array = <HANDLE>;
print @array;
