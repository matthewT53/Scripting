#!/usr/bin/perl -w

# written by Matthew Ta (z5061797) October 2016
# CGI script that updates the password of a given user so they can recover their account
# http://cgi.cse.unsw.edu.au/~cs2041/assignments/matelook/

# bug list:
# * in the store functions, the comment/post/reply number is not extracted from the regex properly
# * If automatically directed to login page check for any random forms

use CGI qw/:all/;
use CGI::Carp qw/fatalsToBrowser warningsToBrowser/;

# use built in date and time libraries to parse dates
$users_dir = "dataset-medium";
main();

sub main{
    print page_header();

    # get the parameters in the url
    my $url_parameters = $ENV{'QUERY_STRING'};

    # get the zid of the user we want to reset in the url
    my $zid = "";
    if ($url_parameters =~ /user=(.*)/){
        $zid = $1;
    }

    # user has finished entering their new password
    if (param("reset_stage") eq "reset_screen_finished"){
        $zid = param("zid_reset");
        my $new_password = param("new_pass_form");
        print update_user_password($zid, $new_password);
    }

    else{
        # as soon as the user opens the link in the email
        print form_reset($zid);
    }

    print page_trailer();
}

# sends a password reset form back to the user
sub form_reset{
    my ($zid) = @_;

    # open the reset form html and send it back to the user
    open RESET_FILE, "<components/reset_form.html" or die "Unable to open reset form";
    my $form_reset_html = join "", <RESET_FILE>;
    $form_reset_html =~ s/\{\{zid\}\}/$zid/g;
    close RESET_FILE;
    return $form_reset_html;
}

# when user has submitted the reset form attempt to reset their password
sub update_user_password{
    my ($zid, $new_password) = @_;

    my $user_details = get_user_details_zid($zid);
    $user_details =~ s/password=.*/password=$new_password/g;
    store_user_details($zid, $user_details);

    open RECOVER_FILE, "<components/recover_pass_success.html" or die "Unable to open recover html file";
    my $password_recover_html = join "", <RECOVER_FILE>;
    close RECOVER_FILE;
    return $password_recover_html;
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
<script src="javascript/reset_password.js"></script>
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
    open $ZID_USER_DET, ">$users_dir/$zid/user.txt" or die "Unable to open user details: $users_dir/$zid/user.txt to store new friends";
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
