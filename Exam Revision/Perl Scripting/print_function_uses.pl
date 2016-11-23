#!/usr/bin/perl -w

# Author: Matthew Ta
# Returns all the c source files where the specified function is used

@c_functions = @ARGV;

foreach $function (@c_functions){
	foreach $file (sort(glob("*.[ch]"))){
		open FILE, "<", "$file" or die "Unable to open: $file for reading";
		print "FILE: $file\n";
		while ($line = <FILE>){
			# function's definition
			if ($line =~ /^[^\s]+\s$function[^;\{]*;/){
				print "$file:$. function $function declared\n";
			}

			# function's use
			elsif ($line =~ /^\s+.*$function/){
				print "$file:$. function $function used\n";
			}

			# function's declaration
			elsif ($line =~ /$function[^\{;]*\{/){
				print "$file:$. function $function defined\n";
			}
		}
		close FILE;
	}	
}
