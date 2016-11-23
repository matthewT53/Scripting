#!/usr/bin/perl -w

# written by Matthew Ta (z5061797) October 2016
# CGI script that confirms the registration of a new user or allows a suer to accept a friend request
# http://cgi.cse.unsw.edu.au/~cs2041/assignments/matelook/

use CGI qw/:all/;
use CGI::Carp qw/fatalsToBrowser warningsToBrowser/;

$users_dir = "dataset-medium";
main();

sub main{
    print page_header();

    # get the parameters in the url
    my $url_parameters = $ENV{'QUERY_STRING'};
    my $user_to_add = "";
    my $user_adding = "";
    if ($url_parameters =~ /add\=(.*)\+(.*)/){
        $user_to_add = $1;
        $user_adding = $2;
        print add_mate($user_to_add, $user_adding);
    }

    else{
        print "<p><b>Error confirming mate request</b></p>"
    }

    print page_trailer();
}

sub add_mate{
    my ($zid_to_add, $zid_doing_adding) = @_;
    my $user1_details = get_user_details_zid($zid_to_add);
    my $user2_details = get_user_details_zid($zid_doing_adding);

    my $user1_name = get_full_name($user1_details);
    my $user2_name = get_full_name($user2_details);
    my $user1_mates = get_mates($user1_details);
    my $user2_mates = get_mates($user2_details);
    my @user1_mates_array = split /\s*,\s*/, $user1_mates;
    my @user2_mates_array = split /\s*,\s*/, $user2_mates;

    push @user1_mates_array, $zid_doing_adding;
    push @user2_mates_array, $zid_to_add;

    $user1_mates = join(", ", @user1_mates_array);
    $user2_mates = join(", ", @user2_mates_array);

    # update both user's friends list
    $user1_details =~ s/mates=.*/mates=\[$user1_mates\]/g;
    $user2_details =~ s/mates=.*/mates=\[$user2_mates\]/g;

    # what if the user has no mates to begin with

    store_user_details($zid_to_add, $user1_details);
    store_user_details($zid_doing_adding, $user2_details);

    # profile picture of the person who is trying to add them
    my $user2_profile = get_profile_pic($zid_to_add);

    # for debugging only - to keep track of mate requests
    open MATE_REQUESTS, "<confirm_mates.txt" or die "Uanble to open mate requests file for reading";
    my $mate_request_details = join "", <MATE_REQUESTS>;
    close MATE_REQUESTS;

    $mate_request_details =~ s/$zid_doing_adding add $zid_to_add//gee;

    open $MATE_REQUESTS, ">confirm_mates.txt" or die "Unable to open mate requests file for writing";
    print $MATE_REQUESTS $mate_request_details;
    close $MATE_REQUESTS;

    # open the end of confirmation page
    open MATE_CONFIRM_PAGE, "<components/confirmed_add.html" or die "Error opening html file for confirming mate request";
    my $mate_request_html = join "", <MATE_CONFIRM_PAGE>;
    close MATE_CONFIRM_PAGE;

    # substitute information into the html page
    $mate_request_html =~ s/\{\{name\}\}/$user2_name/g;
    $mate_request_html =~ s/\{\{profile_pic\}\}/$user2_profile/g;

    return $mate_request_html;
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

sub get_user_details_zid{
    my ($zID) = @_;
    open ZID_USER_DET, "<$users_dir/$zID/user.txt" or die "Unable to open user's details: $users_dir/$zID/user.txt";
    my $details = join '', <ZID_USER_DET>;
    close ZID_USER_DET;
    return $details;
}

sub store_user_details{
    my ($zid, $user_details) = @_;
    open my $ZID_USER_DET, ">$users_dir/$zid/user.txt" or die "Unable to open user details: $users_dir/$zid/user.txt to store new friends";
    print $ZID_USER_DET $user_details;
    close $ZID_USER_DET;
}

sub get_full_name{
    my ($details) = @_;
    my $full_name = "";
    if ($details =~ /full_name\s*=\s*(.*)/){
        $full_name = $1;
    }

    return $full_name;
}

sub get_mates{
	my ($details) = @_;
	my $mates = "";
	if ($details =~ /mates\s*=\s*\[(.*)\]/){
		$mates = $1;
	}

	return $mates;
}

sub get_profile_pic{
    my ($user_zid) = @_;
    my $profile_pic_path = "$users_dir/$user_zid/profile.jpg";
    if (!open(IMAGE_PROFILE, "<$profile_pic_path")){
        $profile_pic_path = "default_prof_pics/default-male.jpg";
    }

    close IMAGE_PROFILE;
    return $profile_pic_path;
}

sub page_trailer {
    my $html = "";
    $html .= join("", map("<!-- $_=".param($_)." -->\n", param())) if $debug;
    $html .= end_html;
    return $html;
}
