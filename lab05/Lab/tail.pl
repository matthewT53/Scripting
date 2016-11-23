#!/usr/bin/perl -w

$n = 10; # default number of lines to print
$printSeperator = 0; # boolean: determines whether to print a sperator or not.

@files = ();
foreach $arg (@ARGV) {
    if ($arg eq "--version") {
        print "$0: version 0.1\n";
        exit(0);
    }
    # handle other options
    # ...
	elsif ($arg =~ /^-[0-9]*$/){
		$arg =~ s/^-//g;
        $n = $arg;
		#print $n, "\n";
	}

    else {
        push @files, $arg;
    }
}

$fileArrSize = $#files + 1; # get the size of the 'files' array (this returns the index of the last element)
if ($fileArrSize > 1){
    $printSeperator = 1;
}

foreach $f (@files) {
    #print "Path 1\n";
    open(File,"<$f") or die "$0: Can't open $f: $!\n";
    @lines = <File>;
    # determine whether we need to print a sperator
    if ($printSeperator == 1){
        print "==> $f <==\n";
    }

    # check to see if the user wants to see more lines than there are in the file
    $start = $#lines - $n + 1;
    if ($start < 0){
        $start = 0;
    }

    for ($i = $start; $i <= $#lines; $i++){
        print $lines[$i];
    }

    close(File);
}

# for when user uses the redirection symbol
if (!@files){
    @lines = {};
    #print "Path 2\n";
    $i = 0;
	while (defined($line = <STDIN>)){
        $lines[$i] = $line;
        $i++;
	}

    # check to see if the user wants to see more lines than there are in the file
    $i = $#lines - $n + 1;
    if ($i < 0){
        $i = 0;
    }

    # print the desired lines
    while ($i <= $#lines){
        $line = $lines[$i];
        print $line;
        $i++;
    }
}
