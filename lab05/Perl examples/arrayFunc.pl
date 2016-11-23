#!/usr/bin/perl -w

open F, "file.txt";
@lines = <F>;
$all = join "", @lines;
print $all;

$all = `date;ps -l`;
$all =~ s/Harry/Hermoine/g; # This is a problem
$all =~ s/Hermoine/Harry/g;


print $all;

# `` backquotes evaluate in shell AND Perl
# =~ regex matching
