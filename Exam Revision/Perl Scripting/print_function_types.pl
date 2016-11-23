#!/usr/bin/perl -w

# Author: Matthew Ta
# Description: Prints all the parmaeters for all functions in a given c source file

foreach $file (@ARGV){
	open FILE, "<", "$file" or die "Unable to open: $file for reading";
	$c_file_contents = join "", <FILE>;
	#print "$c_file_contents\n";
	@function_headers = $c_file_contents =~ /[\w]+\s+[\w\d\_]+\(.*\)\{/g;
	foreach $function_header (@function_headers){
		if ($function_header =~ /([\w]+)\s+([\w\d\_]+)\((.*)\)\{/){
			$function_type = $1;
			$function_name = $2;
			$parameters_string = $3;
		}

		print "function type=\'$function_type\'\n";
		print "function name=\'$function_name\'\n";		
		@parameters = split /\s*,\s*/, $parameters_string;		

		$param_count = 1;
		foreach $param (@parameters){
			if ($param =~ /([\w\d\* ]+)\s+([\w\d]+)/){
				$type = $1;
				$variable = $2;
			}
		
			print "Parameter: $param_count\n" if defined($type);
			print "parameter type=\'$type\'\n" if defined($type);
			print "parameter name=\'$variable\'\n" if defined($variable);
			$param_count++;
		} 

		print "\n";
	}
	close FILE;
}
