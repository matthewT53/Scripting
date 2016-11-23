#!/usr/bin/perl -w
$line_number = 1;
$show_line_num = 0;
$show_control_chars = 0;
@files = ();

# loop through all the arguments
foreach $arg (@ARGV){
    if ($arg eq "-n"){
        $show_line_num = 1;
    }

    elsif ($arg eq "-v"){
        $show_control_chars = 1;
    }

    else{
        push @files, $arg;
    }
}

# traverse each line of the files
foreach $file (@files){
    open FILE, "<", $file or die "Unable to open file";
    while ($line = <FILE>){
        printf "%6d ", $line_number++ if $show_line_num == 1;

        # user wants to see control characters as well
        if ($show_control_chars == 1){
            @characters = split //, $line;
            foreach $ch (@characters){
                $ch_ascii_num = ord($ch);
                # found a control character
                if ($ch_ascii_num < 32){
                    $ch_ascii_num += 64;
                    #print "[DEBUG]: $ch_ascii_num\n";
                    $ch_print = "^" . chr($ch_ascii_num);
                }

                else{
                    $ch_print = $ch;
                }

                print "$ch_print";
            }

            print "\$\n";
        }

        else{
            print "$line";
        }
    }

    close FILE;
}
