#!/usr/bin/perl -w

# written by Matthew Ta (z5061797) October 2016
# CGI script that confirms the registration of a new user or allows a suer to accept a friend request
# http://cgi.cse.unsw.edu.au/~cs2041/assignments/matelook/

# bug list:
# * in the store functions, the comment/post/reply number is not extracted from the regex properly
# * If automatically directed to login page check for any random forms

use CGI qw/:all/;
use CGI::Carp qw/fatalsToBrowser warningsToBrowser/;

# use built in date and time libraries to parse dates

main();

sub main{
    print page_header();

    # get the parameters in the url
    my $url_parameters = $ENV{'QUERY_STRING'};
    if ($url_parameters =~ /new=(.*)/){
        my $zid = $1;
        print new_user($zid);
    }

    else{
        # invalid url
        print "<p><b>Invalid Parameters Sent: Confirmation link broken</b></p>";
    }

    print page_trailer();
}

sub new_user{
    my ($zid) = @_;

    # new user request has been confirmed so
    open $REQUESTS_FILE, "<confirm_requests.txt" or die "Unable to retrieve pending requests";
    my $requests_details = join "", <$REQUESTS_FILE>;
    $requests_details =~ s/$zid//g;
    close $REQUESTS_FILE;
    open $REQUESTS_FILE, ">confirm_requests.txt" or die "Unable to store pending requests";
    print $REQUESTS_FILE $requests_details;
    close $REQUESTS_FILE;

    # return a suitable html
    open CONFIRM_NEW, "<components/confirmed_new.html" or die "Unable to open confirmed_new.html";
    my $new_html = join "", <CONFIRM_NEW>;
    close CONFIRM_NEW;

    return $new_html;
}

sub page_header {
    return <<eof
Content-Type: text/html;charset=utf-8

<!DOCTYPE html>
<html lang="en">
<head>
<title>Matelook</title>
<link href="matelook.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap.min.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap.css" rel="stylesheet">
<script src="bootstrap/js/bootstrap.min.js"></script>
</head>
<body background="backgrounds/new_york.jpg">
eof
}

sub page_trailer {
    my $html = "";
    $html .= join("", map("<!-- $_=".param($_)." -->\n", param())) if $debug;
    $html .= end_html;
    return $html;
}
