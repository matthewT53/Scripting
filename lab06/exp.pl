#!/usr/bin/perl -w
$string = "          <p>Prerequisite: [COMP9201 or COMP9283] and [COMP9331.</p><p><strong>CSS Contribution Charge:</strong>&nbsp;2&nbsp;<a href=https://my.unsw.edu.au/student/fees/StudentContribution.html>(more info)</a></p>";
$string =~ s/<\/p>.*//g;
$string =~ s/^\s*<p>\w+: //g;
@array = split / /, $string;
for $element (@array){
    print "$element.\n";
    if ($element =~ /([A-Za-z]{4}[0-9]{4})/){
        print "$1\n";
    }
}
