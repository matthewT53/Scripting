#!/usr/bin/perl -w

# written by Matthew Ta (z5061797) October 2016
# as a starting point for COMP2041/9041 assignment 2
# http://cgi.cse.unsw.edu.au/~cs2041/assignments/matelook/

use CGI qw/:all/;
use CGI::Carp qw/fatalsToBrowser warningsToBrowser/;

# use built in date and time libraries to parse dates
use DateTime;
use Date::Parse;
use DateTime::Format::ISO8601;

# use built in file directory functions
use File::Path;

# email modules
# use Email::Sender::Simple qw(sendmail);

main();

sub main(){
    # print start of HTML ASAP to assist debugging if there is an error in the script
    print page_header();

    # Now tell CGI::Carp to embed any warning in HTML
    warningsToBrowser(1);

    # define some global variables
    $debug = 0;
    $users_dir = "dataset-medium";
    $comment_reply_id = 0;
    $post_id = 0;

    # print param();

    # check if the user is logged in
    if (param("logged_in") eq "1"){

        # display the background of the user that is being viewed
        if (param("current_page") eq "user_page" || param("current_page") eq "prof_page"){
            my $background_image_path = get_background(param("action_on_user"));
            print "<body background=\"$background_image_path\">";
        }

        else{
            print "<body>";
        }

        # user wants to see a mate's page
        if (param("user_selected") ne "" && param("action") eq ""){
            print user_page(param("user_selected"));
        }

        # user wants to search for something
        elsif (param("search_for") ne ""){
            print search_results_page(param("search_for"));
        }

        # user wants to delete a post, comment or reply
        elsif (param("delete_path") ne ""){
            delete_post();
            if (param("current_page") eq "user_page"){
                print user_page(param("action_on_user"));
            }

            elsif (param("current_page") eq "home_page"){
                print home_page(param("current_user"));
            }

            else{
                print "What page should I load. <br>";
            }
        }

        # user sent a reply
        elsif (param("reply_to_send") ne ""){
            my $reply = param("reply_to_send");
            my $path = param("path_to_comment_reply");
            my $from = param("current_user");
            store_reply($reply, $path, $from);
            if (param("current_page") eq "user_page"){
                print user_page(param("action_on_user"));
            }

            elsif (param("current_page") eq "home_page"){
                print home_page(param("current_user"));
            }

            else{
                print "What page should I load. <br>";
            }
        }

        # user sent a comment
        elsif (param("comment_to_send") ne ""){
            my $comment = param("comment_to_send");
            my $path = param("path_to_comment_reply");
            my $from = param("current_user");
            store_comment($comment, $path, $from);
            if (param("current_page") eq "user_page"){
                print user_page(param("action_on_user"));
            }

            elsif (param("current_page") eq "home_page"){
                print home_page(param("current_user"));
            }

            else{
                print "What page should I load. <br>";
            }
        }

        # user wants to post a comment
        elsif (param("post_to_send") ne ""){
            my $post = param("post_to_send");
            my $from = param("current_user");
            store_post($post, $from);
            if (param("current_page") eq "user_page"){
                print user_page(param("action_on_user"));
            }

            elsif (param("current_page") eq "home_page"){
                print home_page(param("current_user"));
            }

            else{
                print "What page should I load. <br>";
            }
        }

        # user wants to get more mates
        elsif (param("action") eq "add"){
            process_add_mate();
			#print "User on this page: " . param("action_on_user");
            print user_page(param("action_on_user"));
        }

        elsif (param("action") eq "remove"){
            process_remove_mate();
            print user_page(param("action_on_user"));
        }

        # user wants to see the home page
        elsif (param("current_page") eq "home_page"){
            print home_page(param("current_user"));
        }

        elsif (param("current_page") eq "prof_page"){
            print user_page(param("current_user"));
        }

        elsif (param("current_page") eq "settings_page"){
            # user changed their settings
            if (param("details_updated") eq "true"){
                process_updates();
            }

			elsif (param("prof_image_uploaded") eq "true"){
				update_profile_pic();
			}

			elsif (param("back_image_uploaded") eq "true"){
				update_background();
			}

			# can't display settings page of an account that was destroyed
			if (param("destroy") ne "true"){
				print settings_page(param("current_user"));
			}
        }

        else{
            print user_page(param("current_user"));
        }
    }

    else{
        # user wants to sign up
        if (param("welcome_page_action") eq "login"){
            # login attempt was correct
            if (check_login() == 1){
                print "<body>";
                # check to see if the user is registered
                if (is_registered(param("username")) == 0){
                    # user is not registered
                    print "Please check your email to confirm your account with us :) <br>";
                }

                else{
                    # print home_page(param("username"));
    				print home_page(param("username"));
                }
            }

            # subsequent login attempts
            else{
                print "<body background=\"backgrounds/new_york.jpg\">";
                print login_page("Incorrect username or password!");
            }
        }

        elsif (param("welcome_page_action") eq "sign_up"){
            # user has filled in their details so create a dir for them
            if (param("sign_up_complete") eq "1"){
                # check if the user already exists
                if (!does_user_exist(param("zid_form"))){
                    process_new_user();
                    print "<body>";
                    print "We have sent an email to your email address, please verify your account to continue";
                }

                else{
                    print "<body background=\"backgrounds/new_york.jpg\">";
                    print sign_up_page("Error user with that ZID already exists!");
                }

            }

            # first time user clicks sign up
            else{
                print "<body background=\"backgrounds/new_york.jpg\">";
                print sign_up_page();
            }
        }

        # user clicked "forgot password" on login screen
        elsif (param("welcome_page_action") eq "forgot"){
            print "<body background=\"backgrounds/new_york.jpg\">";
            print forgot_password_page();
        }

        # user submitted an email address to recover the password
        elsif (param("welcome_page_action") eq "finish_reset"){
            print "<body background=\"backgrounds/new_york.jpg\">";
            my $result = email_recovery_link(param("email_address"));
            my $message = "";
            # email address wasn't found
            if ($result == 0){
                $message = "Unable to find your email address. Have you registered before?";
            }

            print login_page($message);
        }

        # first time the user comes to our website
        else{
            print "<body background=\"backgrounds/new_york.jpg\">";
			print login_page("");
        }
    }

    print page_trailer();
}

#
# HTML placed at the top of every page
#
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
<link href="css/userpage.css" rel="stylesheet">
<link href="css/post.css" rel="stylesheet">
<link href="css/search.css" rel="stylesheet">
<link href="css/login.css" rel="stylesheet">
<link href="css/settings.css" rel="stylesheet">
<script src="bootstrap/js/bootstrap.min.js"></script>
<script src="bootstrap/js/bootstrap.js"></script>
<script src="javascript/userpage.js"></script>
<script src="javascript/searching.js"></script>
<script src="javascript/login.js"></script>
<script src="javascript/comment.js"></script>
<script src="javascript/settings.js"></script>
<script src="javascript/sha_256.js"></script>
</head>
eof
}

# deletes a post
sub delete_post{
    my $path_delete = param("delete_path");
    rmtree($path_delete) or die "Cannot rmtree $path_delete : $!";
    if (-e $path_delete){
        print "ERROR deleting directory; $path_delete still exists <br>";
    }
}

# returns html code of all mate suggestions
sub get_mate_suggestions{
    my ($current_user) = @_;

    # hash table to keep track of all the likely mates
    my %potential_mates = ();
    # get details about the user
    my $user_details = get_user_details_zid($current_user);
    my $user_mates = get_mates($user_details);
    my @user_mates_array = split /\s*,\s*/, $user_mates;
    my $courses = get_courses($user_details);
    my @courses_array = split /\s*,\s*/, $courses;

    #print "User: $current_user <br>";

    # my mate suggestion algorithm
    foreach my $mate_zid (@user_mates_array){
        my $mate_details = get_user_details_zid($mate_zid);
        my $mates_of_mate = get_mates($mate_details);
        my @mates_of_mate_array = split /\s*,\s*/, $mates_of_mate;
        foreach my $mate_of_mate_zid (@mates_of_mate_array){
            #print "Mate of a mate: $mate_of_mate_zid <br>";
            # ensure current user and this person are not already friends and we have calculated a score for them before
            if ($user_mates !~ /$mate_of_mate_zid/ && !defined($potential_mates{$mate_of_mate_zid}) && $current_user ne $mate_of_mate_zid){
                $potential_mates{$mate_of_mate_zid} = 1;
                my $mate_of_mate_details = get_user_details_zid($mate_of_mate_zid);
                my $mate_of_mate_courses = get_courses($mate_of_mate_details);
                print "My Courses: $courses <br>" if $debug == 1;
                print "Mate of mate courses: $mate_of_mate_courses <br>" if $debug == 1;
                foreach my $current_user_course (@courses_array){
                    print "Current course: $current_user_course <br>" if $debug == 1;
                    # they are taking the same course
                    if ($mate_of_mate_courses =~ /$current_user_course/){
                        $potential_mates{$mate_of_mate_zid}++;
                    }
                }
            }
        }
    }

    # sort all the keys by value
    my @mate_zids = sort { $potential_mates{$b} <=> $potential_mates{$a} } keys %potential_mates;
    #print "Length of keys: $#mate_zids <br>";

    # loop through the hash and construct the html
    my $suggested_html = "";
    my $current_page_num = 1;
    my $current_mate = 0;
    foreach my $mate_zid (@mate_zids){
        # start of a row div
        print "$mate_zid has suggestion score of: " . $potential_mates{$mate_zid} . "<br>" if $debug == 1;
        if ($current_mate % 9 == 0){
            if ($current_page_num == 1){
                $suggested_html .= "<div class=\"row\" id=\"page_$current_page_num\">\n";
            }

            else{
                $suggested_html .= "<div class=\"row\" id=\"page_$current_page_num\" style=\"display: none;\">\n";
            }
        }

        # store the mate's profile pic and name as html
        my $details_mate = get_user_details_zid($mate_zid);
        my $mate_profile = get_profile_pic($mate_zid);
        my $mate_full_name = get_full_name($details_mate);

        # join a mate to the currnet page
        $suggested_html .= "<div class=\"col-xs-4\">
                                <button class=\"thumbnail\" id=\"$mate_zid-thumb\" name=\"$mate_zid\" onclick=\"mate_clicked(this)\" value=\"$mate_zid\">
                                    <img src=\"$mate_profile\" class=\"img-responsive\">
                                    <p class=\"image_text\">$mate_full_name</p>
                                </button>
                            </div>\n";

        # end of a row div
        if ($current_mate % 9 == 8){
            $current_page_num++;
            $suggested_html .= "</div>\n";
        }

        $current_mate++;
    }

    # just to close of the row
    if ($#mates_zid - $current_mate < 9){
        $suggested_html .= "</div>\n";
    }

    # store the max number of pages
    $suggested_html .= "<input type=\"hidden\" name=\"max_page\" id=\"max_page\" value=\"$current_page_num\">\n";

    return $suggested_html;
}

# returns the settings page for the user
sub settings_page{
    my ($zid_user) = @_;
    my $user_details = get_user_details_zid($zid_user);
    open SETTINGS, "<components/settings.html" or die "Unable to open settings html";
    my $settings_html = join "", <SETTINGS>;
    close SETTINGS;

    # substitute the user's data into the html
    my $my_profile_pic = get_profile_pic($zid_user);
    my $background = get_background($zid_user) || "backgrounds/new_york.jpg";
    my $full_name = get_full_name($user_details);
    my $birthday = get_birthday($user_details);
    my $email = get_email_address($user_details);
    my $home = get_home($user_details);
    my $program = get_program($user_details);
    my $courses = get_courses($user_details);

    $settings_html =~ s/\{\{profile_pic\}\}/$my_profile_pic/g;
    $settings_html =~ s/\{\{background_pic\}\}/$background/g;
    $settings_html =~ s/\{\{full_name\}\}/$full_name/g;
    $settings_html =~ s/\{\{birthday\}\}/$birthday/g;
    $settings_html =~ s/\{\{email\}\}/$email/g;
    $settings_html =~ s/\{\{home\}\}/$home/g;
    $settings_html =~ s/\{\{program\}\}/$program/g;
    $settings_html =~ s/\{\{zid\}\}/$zid_user/g;
    $settings_html =~ s/\{\{courses\}\}/$courses/g;

    # get the user's first name
    my $first_name = $full_name;
    if ($full_name =~ /([^\s]*)\s*.*/){
        $first_name = $1;
    }

    $settings_html =~ s/\{\{first_name\}\}/$first_name/g;

    # determine the user's privacy setting, to show the appropriate value in the dropdown
    my $privacy = get_privacy($user_details);
    if ($privacy eq "public"){
        # public profile
        $settings_html =~ s/\{\{public_selected\}\}/selected/g;
        $settings_html =~ s/\{\{friends_selected\}\}//g;
    }

    else{
        # friends only
        $settings_html =~ s/\{\{friends_selected\}\}/selected/g;
        $settings_html =~ s/\{\{public_selected\}\}//g;
    }

    return $settings_html;
}

# determines which settings should be updated
sub process_updates{
	# user wants to update basic info
    if (param("new_name") ne ""){
		print "New name <br>";
        update_details();
    }

	elsif (param("new_password") ne ""){
		print "Changing password <br>";
		update_password();
	}

    elsif (param("visibility") ne ""){
		print "Changing visibility <br>";
        update_privacy();
    }

    elsif (param("suspend") ne ""){
		print "Suspending account <br>";
        suspend_account();
    }

    elsif (param("destroy") ne ""){
		print "Destroying account <br>";
        destroy_account();
    }

    else{
        print "What are you trying to change??? <br>";
    }
}

# updates the user's profile picture with a file uploaded
sub update_profile_pic{
	print "Uploading profile picture <br>" if $debug == 1;
    my $current_user_zid = param("current_user");
    my $user_path = "$users_dir/$current_user_zid/profile.jpg";

    # get the name and handle of the file we are trying to receive
    my $file_handle = upload("upload_image");

    # get the file from the client
    receive_file($user_path, $file_handle);
}

# updates theu ser's background picture
sub update_background{
    my $current_user_zid = param("current_user");
    my $user_path = "$users_dir/$current_user_zid/background.jpg";

    # get the name and handle of the file we are trying to receive
    my $file_handle = upload("upload_background");

    # get the file from the client
    receive_file($user_path, $file_handle);
}

# receives a file the user has uploaded
sub receive_file{
    my ($dir_pic, $file_handle) = @_;
    open FILE_OUT, ">$dir_pic" or "Unable to open profile image for user: $dir_pic";
    binmode(FILE_OUT);
    # file writing variables
    my $bytes_read = 0;
    my $total_bytes = 0;
    my $buffer = "";
    my $buf_size = 4096;

    while ($bytes_read = read($file_handle, $buffer, $buf_size)){
        print FILE_OUT $buffer;
        $total_bytes += $bytes_read;
    }

    close FILE_OUT;
}

# updates the user's details
sub update_details{
    # get the user's updated information
    my $name = param("new_name");
    my $birthday = param("new_birthday");
    my $email = param("new_email");
    my $home = param("new_home");
    my $program = param("new_program");
    my $password = param("new_password");
    my $zid = param("current_user");
    my $about_me = param("new_about_me");
    my $courses = param("new_courses");

    # create the contents of the new file
    my $user_details = get_user_details_zid($zid);

	# some of these details may not already exist
	# update full name
	if ($user_details =~ /full_name=.*/){
		$user_details =~ s/full_name=.*/full_name=$name/g;
	}

	else{
		$user_details .= "full_name=$name\n";
	}

	# update birthday
	if ($user_details =~ /birthday=.*/){
		$user_details =~ s/birthday=.*/birthday=$birthday/g;
	}

	else{
		$user_details .= "birthday=$birthday\n";
	}

	# update email addr
	if ($user_details =~ /email=.*/){
		$user_details =~ s/email=.*/email=$email/g;
	}

	else{
		$user_details .= "email=$email\n";
	}

	# update home
	if ($user_details =~ /suburb=.*/){
		$user_details =~ s/suburb=.*/suburb=$home/g;
	}

	else{
		$user_details .= "suburb=$home\n";
	}

	# update program
	if ($user_details =~ /program=.*/){
		$user_details =~ s/program=.*/program=$program/g;
	}

	else{
		$user_details .= "program=$program\n";
	}

    # update about me
    if ($user_details =~ /about=.*/){
        $user_details =~ s/about=.*/about=$about_me/g;
    }

    else{
        $user_details .= "about=$about_me\n";
    }

    # update courses
    if ($user_details =~ /courses=.*/){
        $user_details =~ s/courses=.*/courses=\[$courses\]/g;
    }

    else{
        $user_details .= "courses=[$courses]\n";
    }

    store_user_details($zid, $user_details);
}

sub update_password{
	my $zid = param("current_user");
	my $user_details = get_user_details_zid($zid);
	my $password = param("new_password");

	$user_details =~ s/password=.*/password=$password/g;
	store_user_details($zid, $user_details);
}

# makes a user's account public or friends
sub update_privacy{
    my $zid = param("current_user");
    my $user_details = get_user_details_zid($zid);
    my $new_setting = param("visibility");

    # update the privacy setting
    $user_details =~ s/privacy=.*/privacy=$new_setting/g;
    store_user_details($zid, $user_details);
}

# suspends a user's account
sub suspend_account{
    my $zid = param("current_user");
    my $user_details = get_user_details_zid($zid);
    my $new_acc_state = param("suspend");
    if ($new_acc_state eq "true"){
        $user_details =~ s/suspend=.*/suspend=true/g;
        store_user_details($zid, $user_details);
    }
}

# deletes a user's account
sub destroy_account{
    print "Destroying account $zid <br>" if $debug == 1;
    my $zid = param("current_user");
    my $user_path = "$users_dir/$zid";

    rmtree($user_path) or die "Cannot rmtree $user_path : $!";
    if (-e $user_path){
        print "ERROR deleting directory; $user_path still exists <br>";
    }
}

# returns a password recovery form to the browser
sub forgot_password_page{
    open RECOVER_FILE, "<components/recover_pass.html" or die "Unable to open password recovery form";
    my $recover_file_html = join "", <RECOVER_FILE>;
    close RECOVER_FILE;
    return $recover_file_html;
}

# user filled out their email address
# this subroutine emails the user with a link to reset their password
sub email_recovery_link{
    my ($email_addr_user) = @_;
    my $full_name = "";
    my $email_found = 0;
	my $zid = "";
	my $email_addr = "";

    # search through all the users to find the email address specified
    my @users_dir = sort(glob("$users_dir/*"));
    foreach my $path (@users_dir){
        $path =~ s/\Q$users_dir\///g;
		$zid = $path;
		print "$zid<br>" if $debug == 1;
        my $user_details = get_user_details_zid($zid);
        $email_addr = get_email_address($user_details);
		print "Send to: $email_addr<br>" if $debug == 1;
        # user's email address was found
        if ($email_addr_user eq $email_addr){
            $email_found = 1;
            last;
        }
    }

    # email address was found for a lost mate account
    if ($email_found == 1){
        # send an email to the mate the current user is trying to add
        open(MAIL, "|/usr/sbin/sendmail -t");
        print MAIL "To: $email_addr\n";
        print MAIL "From: matelook\@gmail.com\n";
        print MAIL "Subject: Matelook, New Mate Request\n\n";

        # need to get the url of this cgi script
        my $url = $ENV{'SCRIPT_URI'};
        $url =~ s/matelook\.cgi/recover_password\.cgi/g;
        print MAIL "Hey $full_name, please follow this link to reset your password $url?user=$zid\n";
        close(MAIL);
    }

    return $email_found;
}

# returns a sign up page
sub sign_up_page{
    my ($error_msg) = @_;
    open SIGN_UP_FILE, "<components/sign_up.html" or die "Unable to open sign up component";
    my $sign_up_html = join "", <SIGN_UP_FILE>;
    close SIGN_UP_FILE;

    # show error message
    $sign_up_html =~ s/\{\{error_message\}\}/$error_msg/g;
    $sign_up_html =~ s/display\: none\;//g;
    return $sign_up_html;
}

sub process_add_mate{
    print "Adding new user<br>" if $debug == 1;
    my $current_zid = param("current_user");
    my $zid_to_add = param("action_on_user");

    # get details for both users
    my $user_to_add_details = get_user_details_zid($zid_to_add);
    my $current_user_details = get_user_details_zid($current_zid);
    my $user_to_add_email = get_email_address($user_to_add_details);
    my $current_name = get_full_name($current_user_details);
    my $user_to_add_name = get_full_name($user_to_add_details);

    # send an email to the mate the current user is trying to add
    open(MAIL, "|/usr/sbin/sendmail -t");
    print MAIL "To: $user_to_add_email\n";
    print MAIL "From: matelook\@gmail.com\n";
    print MAIL "Subject: Matelook, New Mate Request\n\n";

    # need to get the url of this cgi script
    my $url = $ENV{'SCRIPT_URI'};
    $url =~ s/matelook\.cgi/add_mate\.cgi/g;
    print MAIL "Hey $user_to_add_name!\nA mate by the name of $current_name would like to add you as a mate\n" .
                "To accept their request, please follow the link: $url?add=$current_zid+$zid_to_add";
    close(MAIL);

    # store in the pending mate requests file confirm_mate.txt
    open MATE_REQ, "<confirm_mates.txt" or die "Unable to open file containing mate requests for reading";
    my $mate_req_details = join "", <MATE_REQ>;
    close MATE_REQ;

    open my $MATE_REQ, ">confirm_mates.txt" or die "Unable to open mate reqeusts file for writing";
    $mate_req_details = $mate_req_details . "$current_zid add $zid_to_add\n";
    print $MATE_REQ $mate_req_details;
    close $MATE_REQ;
}

sub process_remove_mate{
    print "I am removing mate<br>" if $debug == 1;
	my $current_zid = param("current_user");
	my $user_to_remove = param("action_on_user");

	# get details for both users
    my $current_details = get_user_details_zid($current_zid);
    my $user_to_remove_details = get_user_details_zid($user_to_remove);

    my $mates_current = get_mates($current_details);
    my $mates_remove = get_mates($user_to_remove_details);

    print "[BEFORE REMOVAL]: <br>" if $debug == 1;
    print "Current mates: $mates_current <br>" if $debug == 1;
    print "Remove mates: $mates_remove <br>" if $debug == 1;

    # remove the relationship between the two mates
	if ($mates_current =~ /^\s*$user_to_remove/){
		$mates_current =~ s/^\s*$user_to_remove\s*\,\s*//g;
	}

	else{
		$mates_current =~ s/\s*,?\s*$user_to_remove//g;
	}

	if ($mates_remove =~ /^\s*$current_zid/){
		$mates_remove =~ s/^\s*$current_zid\s*\,\s*//g;
	}

	else{
		$mates_remove =~ s/\s*,?\s*$current_zid//g;
	}

    print "[AFTER REMOVAL]: <br>" if $debug == 1;
    print "Current mates: $mates_current <br>" if $debug == 1;
    print "Remove mates: $mates_remove <br>" if $debug == 1;

    $current_details =~ s/mates=.*/mates=\[$mates_current\]/g;
    $user_to_remove_details =~ s/mates=.*/mates=\[$mates_remove\]/g;

	print "[USER DETAILS]: <br>" if $debug == 1;
	print "Current user details: $current_details <br>" if $debug == 1;
	print "User to remove details: $user_to_remove_details <br>" if $debug == 1;

    # update the detaisl of both users
    store_user_details($current_zid, $current_details);
    store_user_details($user_to_remove, $user_to_remove_details);
}


# create a new directory for the new user
sub process_new_user{
    my $zid = param("zid_form");
    my $email = param("email_form");
    my $password = param("password_form");
    my $name = param("name_form");
    my $birthday = param("birthday_form");
    my $home = param("home_form");

    # create the contents of user.txt for the new user
    my $new_file_contents = "zid=$zid\npassword=$password\nhome_suburb=$home\nemail=$email\nfull_name=$name\nbirthday=$birthday\nprogram=\nmates=[]\ncourses=[]\nprivacy=public\nsuspend=false\n";
    mkdir "$users_dir/$zid/", 0755; # create dir for user
    mkdir "$users_dir/$zid/posts/", 0755; # create dir for posts

    # send an email to the new user
    open(MAIL, "|/usr/sbin/sendmail -t");
    print MAIL "To: $email\n";
    print MAIL "From: matelook\@gmail.com\n";
    print MAIL "Subject: Matelook account verification\n\n";

    # need to get the url of this cgi script
    my $url = $ENV{'SCRIPT_URI'};
    $url =~ s/matelook\.cgi/confirm\.cgi/g;
    print MAIL "Hey $name!, Please verify your account by going to : $url?new=$zid";
    close(MAIL);

    # store the pending confirmation request in a file
    open $REQUESTS_FILE, "<confirm_requests.txt" or die "Unable to retrieve pending requests";
    my $requests_details = join "", <$REQUESTS_FILE>;
    $requests_details = $requests_details . "\n$zid";
    close $REQUESTS_FILE;
    open $REQUESTS_FILE, ">confirm_requests.txt" or die "Unable to store pending requests";
    print $REQUESTS_FILE $requests_details;
    close $REQUESTS_FILE;

    # write the new user's info into a dir on the system
    open $USER_FILE, ">$users_dir/$zid/user.txt" or die "Error creating new dir for user: $zid name: $name";
    print $USER_FILE $new_file_contents;
    close $USER_FILE;
}

# check if user zid already exists
sub does_user_exist{
    my ($zid) = @_;
    my $user_exists = 0;
    my @user_paths = sort(glob("$users_dir/*"));
    my $user_paths_str = join " ", @user_paths;
    my $user_path = "$users_dir/$zid";

    # check if the user exists
    if ($user_paths_str =~ /$user_path/){
        $user_exists = 1;
    }
    return $user_exists;
}

# stores a comment into our collection
sub store_comment{
    print "Storing Comment<br>" if $debug == 1;
    my ($comment, $path, $from) = @_;
    # note the path may contain other comments so we need to add it with the appropriate number
    my @comments_paths = sort(glob("$path*"));
	my @comment_ids = ();
	foreach my $comment_id (@comments_paths){
		$comment_id =~ s/$path//g;
		push @comment_ids, $comment_id;
	}

	@comment_ids = sort {$a <=> $b} @comment_ids;
    my $length = $#comment_ids;
    my $comment_num = 0;
    if ($length != -1){
        $comment_num = $comment_ids[$length] + 1;
    }

    my $time = DateTime->now()->iso8601();
    my $file = "from=$from\ntime=$time\nmessage=$comment\n";
    print "Path = $path<br>" if $debug == 1;
    print "File = $file<br>" if $debug == 1;
    print "Dir_to_create = $path$comment_num<br>" if $debug == 1;
    print "comment_num = $comment_num<br>" if $debug == 1;

    # create the directory
    mkdir("$path", 0755);
	mkdir("$path$comment_num", 0755);

    # write the comment to file
    open my $NEW_COMMENT, ">$path$comment_num/comment.txt" or die "Unable to create file: $path$comment_num/comment.txt\n";
    print $NEW_COMMENT $file;
    close $NEW_COMMENT;
}

# stores a reply to a comment in our collection
sub store_reply{
    print "Storing reply<br>" if $debug == 1;
    my ($reply, $path, $from) = @_;
    # note the path may contain other comments so we need to add it with the appropriate number
    my @replies_paths = sort(glob("$path*"));
	my @reply_ids = ();
	foreach my $reply_id (@replies_paths){
		$reply_id =~ s/$path//g;
		push @reply_ids, $reply_id;
	}

	@reply_ids = sort {$a <=> $b} @reply_ids;
    my $length = $#reply_ids;
    my $comment_num = 0;

    # check if first reply
    if ($length != -1){
        $comment_num = $reply_ids[$length] + 1;
    }

    my $time = DateTime->now()->iso8601();
    my $file = "from=$from\ntime=$time\nmessage=$reply\n";

    print "Path = $path<br>" if $debug == 1;
    print "File = $file<br>" if $debug == 1;

    # create the directory
    mkdir("$path", 0755);
	mkdir("$path$comment_num", 0755);

    # write the comment to file
    open my $NEW_REPLY, ">$path$comment_num/reply.txt" or die "Unable to create file: $path$comment_num/reply.txt";
    print $NEW_REPLY $file;
    close $NEW_REPLY;
}

# stores a post for the current user
sub store_post{
    my ($post, $from) = @_;
    my @posts_paths = sort(glob("$users_dir/$from/posts/*"));
	my @post_ids = ();
    my $path = "$users_dir/$from/posts/";

	foreach my $post_id (@posts_paths){
		$post_id =~ s/$path//g;
        print "Post Id: $post_id <br>" if $debug == 1;
		push @post_ids, $post_id;
	}

	@post_ids = sort {$a <=> $b} @post_ids;

    my $last_index = $#post_ids;

    # check if first post
    my $comment_num = 0;
    if ($last_index != -1){
        $comment_num = $post_ids[$last_index] + 1;
    }

    print "Comment num: $comment_num <br>" if $debug == 1;
    my $time = DateTime->now()->iso8601();
    my $file = "from=$from\ntime=$time\nmessage=$post\n";
	my $path_to_create = "$users_dir/$from/posts/$comment_num";

    if (mkdir("$path_to_create", 0755) == 0){
		print "Error creating directory: $path_to_create <br>";
	}

    open my $NEW_POST, ">$path_to_create/post.txt" or die "Unable to create file: $path_to_create/post.txt\n";
    print $NEW_POST $file;
    close $NEW_POST;
}

# returns the login page for the user
# also includes a message indicating whether a login attemp was correct or not
sub login_page{
	my ($error_message) = @_;
    my $login_page_html = "";
    open LOGIN_PAGE, "<components/login.html" or die "Unable to open login page";
    $login_page_html = join "", <LOGIN_PAGE>;

	# add error message if there is one
	if ($error_message ne ""){
		$login_page_html =~ s/\{\{error_message\}\}/$error_message/g;
		$login_page_html =~ s/display: none;//g;
	}
    close LOGIN_PAGE;
    return <<eof;
$login_page_html
eof
}

sub check_login{
    my $username = param("username");
    my $password = param("password");
    my $user_exists = 0;
    my @user_paths = sort(glob("$users_dir/*"));

    # try to find the user in our collection
    foreach my $user_dir (@user_paths){ # change this to a binary search later
        if ($user_dir =~ /$username/){
            open USER_FILE, "<$user_dir/user.txt" or die "Unable to open user.txt for $user_dir";
            my $user_details = join "", <USER_FILE>;
            if ($user_details =~ /password\s*=\s*(.*)/){
                if ($password eq $1){
                    $user_exists = 1;
                }
            }
            close USER_FILE;
            last;
        }
    }
    return $user_exists;
}

# checks whether username and password fields have been entered
sub user_details_entered{
    my $username = param("username");
    my $password = param("password");
    my $details_entered = 0;

    # check that the user actually netref something
    if ($username ne "" && $password ne ""){
        $details_entered = 1;
    }

    return $details_entered;
}

# returns the homepage for a given ZID
sub home_page{
    my ($zid) = @_;
	my $home_page_html = "";
	my @related_content = (); # any post that mentions the current user
	my @user_paths = sort(glob("$users_dir/*"));
    #print "Path = $users_dir/$zid/user.txt\n";
	my $users_details = get_user_details("$users_dir/$zid/user.txt");
    #print "Made it here\n";
	my $users_mates_str = get_mates($users_details);
	my $full_name = get_full_name($users_details);
    my $image_path = get_profile_pic($zid);

    # get a list of the current's user's mates as zids and fullnames
    my @users_mates_zids = split /\s*,\s*/, $users_mates_str;
	my $users_mates_fullnames_str = convert_zid_fullname($users_mates_str);
	my @users_mates_fullnames = split /\s*,\s*/, $users_mates_fullnames_str;

    # hash where key is date and value is the directory
    my %recent_content = ();

    # limit the number of posts that are displayed
    my $max_posts_displayed = 8;
    my $posts_added = 0;

	# search through the directories of each user
	foreach my $another_user_path (@user_paths){
		my @posts_dir_mate = sort(glob("$another_user_path/posts/*"));
        # loop through all the posts for a user
        foreach my $post_path (@posts_dir_mate){
            open POST_FILE, "<$post_path/post.txt" or die "Unable to open: $post_path/post.txt";
            my $post_details = join "", <POST_FILE>;
            my $time_posted = get_time($post_details);
            $time_posted =~ s/\+\d*//g;
            $recent_content{$time_posted} = $post_path;
            close POST_FILE;
        }
	}

    # sort the hash table based on the keys (times)
    my @sorted_times = sort by_recent_time keys %recent_content;

    # push all the related posts to @related_content
    foreach my $time (@sorted_times){
        # check if the post is relevent and recent
        my $post_file_path = $recent_content{$time};
        # print "Time = $time and Path = $recent_content{$time}\n";
        my $post_html = get_post($post_file_path);
        $post_html =~ s/\{\{date_posted\}\}/$time/g;

        # prevent too many posts from being displayed
        if ($posts_added < $max_posts_displayed){
            # check if the current user was tagged in anything
            if ($post_html =~ /$full_name/){
                push @related_content, $post_html;
                $posts_added++;
            }

            else{
                # check if the post was from any of the user's mates
                foreach my $mate_fullname (@users_mates_fullnames){
                    if ($post_html =~ /$mate_fullname Posted:/){
                        push @related_content, $post_html;
                        $posts_added++;
                    }
                }
            }
        }
    }

	# open the home page html file
	open HOME_PAGE, "<components/home.html" or die "Unable to open home page";
	$home_page_html = join "", <HOME_PAGE>;
	close HOME_PAGE;
	# get user details to substitute into the html
	my $first_name = $full_name;
	if ($first_name =~ /([^\s]*)\s*.*/){
		$first_name = $1;
	}

	my $related_content_html = join "", @related_content;
    my $suggested_mates = get_mate_suggestions($zid);

	$home_page_html =~ s/\{\{first_name\}\}/$first_name/g;
	$home_page_html =~ s/\{\{related_posts\}\}/$related_content_html/g;
	$home_page_html =~ s/\{\{profile_pic\}\}/$image_path/g;
    $home_page_html =~ s/\{\{zid\}\}/$zid/g;
    $home_page_html =~ s/\{\{suggested_mates\}\}/$suggested_mates/g;
    return <<eof;
$home_page_html
eof
}

# searches the database looking for anything that matches the search string
sub search_results_page{
    my ($string_to_search) = @_;
    my @results_list = ();
    my $results_page = "";
    my $results_list_string = "";
    my $limit = 15;
    my $i = 0;

    $string_to_search = lc $string_to_search;

    # get the directory of everything in our database
    @users_database = sort(glob("$users_dir/*"));
    foreach my $path_to_user (@users_database){
        my $mate_details = get_user_details("$path_to_user/user.txt");
        my $mates_name = lc get_full_name($mate_details);
        my $zid = get_zid($mate_details);
        my $image_path = get_profile_pic($zid);
        # search string matches a user's name
        # print "[SEARCHING]: Mates name: $mates_name and searching for: $string_to_search\n";
        if ($mates_name =~ /$string_to_search/){
            open RESULTS_LIST, "<components/results_list.html" or die "Unable to open results list";
            my $list_html = join "", <RESULTS_LIST>;
            close RESULTS_LIST;

            # substitute the information from the results into results_list.html
            $list_html =~ s/\{\{full_name\}\}/$mates_name/g;
            $list_html =~ s/\{\{profile_pic\}\}/$image_path/g;
            $list_html =~ s/\{\{zid\}\}/$zid/g;

            push @results_list, $list_html;
        }

        # allow the user to search for posts as well
        my @paths_to_posts = sort(glob("$path_to_user/posts/*"));
        foreach my $path_post (@paths_to_posts){
            open POST_FILE, "<$path_post/post.txt" or die "Unable to open: $path_post/post.txt";
            my $post_details = join "", <POST_FILE>;
            my $post_message = lc get_message($post_details);
            close POST_FILE;

            if ($i < $limit){
                if ($post_message =~ /$string_to_search/){
                    push @results_list, get_post($path_post);
                    $i++;
                }
            }
        }
    }

    # substitute all this information back into search_results.html
    open RESULTS_PAGE, "<components/search_results.html" or die "Unable to open seach_results.html";
    $results_page = join "", <RESULTS_PAGE>;
    close RESULTS_PAGE;
    # no results were found
    if ($#results_list != -1){
        $results_list_string = join '', @results_list;
    }

    else{
        $results_list_string = "No results found, Try Again";
    }

    # sub in the search term as well as the results list
    my $current_user = param("current_user");
    $results_page =~ s/\{\{search_term\}\}/$string_to_search/g;
    $results_page =~ s/\{\{search_results\}\}/$results_list_string/g;
    $results_page =~ s/\{\{zid\}\}/$current_user/g;

    return <<eof;
$results_page;
eof
}


#
# Show unformatted details for user "n".
# Increment parameter n and store it as a hidden variable
#
sub user_page {
    my ($user_to_show) = @_;
    my @users = sort(glob("$users_dir/*"));
    # allow any user's page to be displayed
    $details_filename = "$users_dir/$user_to_show/user.txt";
    $imagePath = "$users_dir/$user_to_show/profile.jpg";
    $user_to_show = "$users_dir/$user_to_show";

    my $details = get_user_details($details_filename);

    # details of the user we want to display
    my $userMates = get_mates($details);
    my @mates = split /\s*,\s*/, $userMates;
    my @mates_html = ();
    my $mates_html_string = "";
    my $full_name = get_full_name($details);
    my $program = get_program($details);
    my $birthday = get_birthday($details);
    my $home = get_home($details);
    my $zid = get_zid($details);
    my $about_user = get_about_me($details);

    # check if a profile picture exists, if not use the default picture
    if (!open(IMAGE, "<$imagePath")){
      $imagePath = "default_prof_pics/default-male.jpg";
      # pick a different one depending on gender
    }
    close IMAGE;

    foreach my $mate (@mates){
        # get the profile picture of the mate if there is one
        # check if a profile picture exists, if not use the default picture
        my $mateProfilePic = "$users_dir/$mate/profile.jpg";
        my $mateDetails = get_user_details("$users_dir/$mate/user.txt");
        my $matesName = get_full_name($mateDetails);
        if (!open(IMAGE, "<$mateProfilePic")){
          $mateProfilePic = "default_prof_pics/default-male.jpg";
          # pick a different one depending on gender
        }
        close IMAGE;
        push @mates_html,
        "<div class=\"col-xs-4 div_size_thumbnail imgWrap\">
            <button class=\"thumbnail\" id=\"$mate-thumb\" name=\"$mate\" onclick=\"mate_clicked(this)\" value=\"$mate\">
                <img src=\"$mateProfilePic\" class=\"img-responsive\">
                <p class=\"image_text imgDescription\">$matesName</p>
            </button>
        </div>";
    }

    # join the array of mates into a single string of html code
    $mates_html_string = join("\n", @mates_html);


    # get the html for the user's page
    open USER_PAGE, "<components/user_page.html" or die "Unable to open the HTML of user's page.";
    my $user_page_html = join "", <USER_PAGE>;
    close USER_PAGE;

    # fetch the user's posts here
    $posts = get_all_posts($user_to_show);
    my $user_logged_in = param("current_user");

    my $user_view_privacy = get_privacy($details);
    my $is_suspended = get_suspended($details);
    my $suggested_mates = get_mate_suggestions($user_logged_in);

    # the profile you are trying to view is friends only and you are nto a friend
    if (($user_view_privacy eq "friends" && $userMates !~ /$user_logged_in/) || $is_suspended eq "true"){
        $user_page_html =~ s/\{\{full_name\}\}//g;
        $user_page_html =~ s/\{\{program\}\}//g;
        $user_page_html =~ s/\{\{birthday\}\}//g;
        $user_page_html =~ s/\{\{home\}\}//g;
        $user_page_html =~ s/\{\{mates\}\}//g;
        #$user_page_html =~ s/\{\{zid\}\}//g;
		if ($is_suspended eq "true"){
			$user_page_html =~ s/\{\{posts\}\}/ACCOUNT SUSPENDED BY USER/g;
		}

		else{
			$user_page_html =~ s/\{\{posts\}\}/This is a private account, send a mate request to view/g;
		}

        $user_page_html =~ s/\{\{profile_pic\}\}//g;
        $user_page_html =~ s/\{\{n\}\}//g;
        $user_page_html =~ s/\{\{first_name\}\}//g;
        $user_page_html =~ s/\{\{about_me\}\}//g;
        $user_page_html =~ s/\{\{suggested_mates\}\}//g;
    }

    else{
        # sub user's info into the HTML template
        $user_page_html =~ s/\{\{full_name\}\}/$full_name/g;
        $user_page_html =~ s/\{\{program\}\}/$program/g;
        $user_page_html =~ s/\{\{birthday\}\}/$birthday/g;
        $user_page_html =~ s/\{\{home\}\}/$home/g;
        $user_page_html =~ s/\{\{mates\}\}/$mates_html_string/g;
       #$user_page_html =~ s/\{\{zid\}\}/$user_logged_in/g;
        $user_page_html =~ s/\{\{posts\}\}/$posts/g;
        $user_page_html =~ s/\{\{profile_pic\}\}/$imagePath/g;
        $user_page_html =~ s/\{\{n\}\}/$next_user/g;
        $user_page_html =~ s/\{\{first_name\}\}/$first_name/g;
        $user_page_html =~ s/\{\{about_me\}\}/$about_user/g;
        $user_page_html =~ s/\{\{suggested_mates\}\}/$suggested_mates/g;
    }

	$user_page_html =~ s/\{\{page_zid\}\}/$zid/g;
	$user_page_html =~ s/\{\{zid\}\}/$user_logged_in/g;

    # get the logged in user's mates
    my $add_button_html = "<div style=\"padding-top: 5%;\">
                                <button class=\"btn btn-success btn-lg\" onclick=\"add_mate()\">Add Mate</button>
                          </div>";

    my $remove_button_html = "<div style=\"padding-top: 5%;\">
                                <button class=\"btn btn-danger btn-lg\" onclick=\"remove_mate()\">Remove Mate</button>
                             </div>";
	if ($is_suspended ne "true"){
		my $logged_in_user_details = get_user_details_zid($user_logged_in);
		my $logged_in_user_mates = get_mates($logged_in_user_details); # this contains zids

		# if the user selected is a friend of the user logged in then they have the option to remove
		if ($logged_in_user_mates =~ /$zid/){
		    $user_page_html =~ s/\{\{action\}\}/$remove_button_html/g;
		}

		elsif ($user_logged_in eq $zid){
		    $user_page_html =~ s/\{\{action\}\}//g;
		}

		else{
		    $user_page_html =~ s/\{\{action\}\}/$add_button_html/g;
		}
	}

    # if the user selected is the same as the logged in user then hide the post box
    open STATUS, "<components/status.html" or die "Unable to open status box";
    my $status_html = join "", <STATUS>;
    close STATUS;

    # get the user's first name
    my $first_name = $full_name;
	if ($first_name =~ /([^\s]*)\s*.*/){
		$first_name = $1;
	}

    # determine if a box to update the status should appear
    if ($user_logged_in eq $zid){
        $status_html =~ s/\{\{first_name\}\}/$first_name/g;
        $user_page_html =~ s/\{\{update_status\}\}/$status_html/g;
    }

    else{
        $user_page_html =~ s/\{\{update_status\}\}//g;
    }

    return <<eof
$user_page_html
eof
}

#
# Processes all the posts made by a User and returns HTML containing the posts
# Overall O(P x C x R) time complexity
#
sub get_all_posts{
    my ($user_path) = @_;
    my @post_paths = reverse sort(glob("$user_path/posts/*"));
    my $post_html_string = "";
    my @all_posts = ();
    my %most_recent_posts = ();

	#my $my_details = get_user_details("$user_path/user.txt");
    # store all the post paths in a hash with their time posted as the key
    foreach my $path_to_post (@post_paths){
        open POST_FILE, "<$path_to_post/post.txt" or die "Unable to post file: $path_to_post/post.txt";
        my $post_details = join "", <POST_FILE>;
        my $time_posted = get_time($post_details);
        $time_posted =~ s/\+\d*//g;
        $most_recent_posts{$time_posted} = $path_to_post;
        close POST_FILE;
    }

    my @sorted_times = sort by_recent_time keys %most_recent_posts;

    # loop through each of the posts
    foreach my $time_of_post (@sorted_times){
        my $post_dir = $most_recent_posts{$time_of_post};
        my $post_html = get_post($post_dir);
        $post_html =~ s/\{\{date_posted\}\}/$time_of_post/g;
        push @all_posts, $post_html;
    }

    $post_html_string = join("\n", @all_posts);

    return <<eof
$post_html_string
eof
}

# gets a single post for a user
# expects to be given the path to posts as well as the zid
sub get_post{
	my ($post_dir) = @_;
	my @post_html = ();
    my $post_html_joined = "";
	my $comments_html = "";

	open FILE_POST, "<$post_dir/post.txt" or die "Unable to open posts file: $post_dir/post.txt";
    my $thisPost = join "", <FILE_POST>;

    # get information about the person who posted
    my $zid_from = get_from($thisPost);
    my $from_name = zid_to_fullname($zid_from);
    my $profile_pic = get_profile_pic($zid_from);
	my $post = get_message($thisPost);

    # replace any ZIDS in the post with the full name
	$post = convert_zid_fullname_links($post);

    # need to get comments and replies as well
    $comments_html = get_comments($post_dir);
	open POST_BOX, "<components/post_box.html" or die "Unable to open posts template";

	# read in the html code for the post box
	@post_html = <POST_BOX>;
    $post_html_joined = join "", @post_html;

	# sub in the name of the mate who made the post
    my $path_for_comments = "$post_dir/comments/";
	$post_html_joined =~ s/\{\{full_name\}\}/$from_name/g;
	$post_html_joined =~ s/\{\{post\}\}/$post/g;
	$post_html_joined =~ s/\{\{box_comments\}\}/$comments_html/g;
    $post_html_joined =~ s/\{\{profile_pic\}\}/$profile_pic/g;
    $post_html_joined =~ s/\{\{path_to_post\}\}/$path_for_comments/g;
    $post_html_joined =~ s/\{\{zid\}\}/$zid_from/g;

    # give each post box a unique id
    my $comment_id = "post_$post_id";
    $post_html_joined =~ s/\{\{post_id\}\}/$comment_id/g;
    $post_html_joined =~ s/\{\{post_num\}\}/$post_id/g;

    $post_id++;

    # determine whether we need to display a close button
    # if the person who owns the post isn't the person who is logged in they should be able to delete
    # the post
    my $delete_button_html = "<button type=\"button\" class=\"close\" aria-hidden=\"true\" name=\"$post_dir\" onclick=\"delete_post(this)\">&times;</button>";
    my $current_user = param("current_user") || param("username");
    if ($current_user eq $zid_from){
        $post_html_joined =~ s/\{\{delete_button\}\}/$delete_button_html/g;
    }

    else{
        $post_html_joined =~ s/\{\{delete_button\}\}//g;
    }

	close POST_BOX;
    close FILE_POST;

	return $post_html_joined;
}

# return the comments to a post
sub get_comments{
    my ($post_dir) = @_;
    my @comments_paths = reverse sort(glob("$post_dir/comments/*"));
    my @comments_html = ();
    my $comments_html_joined = "";
    my $replies_html = "";
    my @all_comments = ();
    my %most_recent_comments = ();

    foreach my $path_to_comment (@comments_paths){
        open COMMENT_FILE, "<$path_to_comment/comment.txt" or die "Unable to comment file: $path_to_comment/comment.txt";
        my $comment_details = join "", <COMMENT_FILE>;
        my $time_posted = get_time($comment_details);
        $time_posted =~ s/\+\d*//g;
        $most_recent_comments{$time_posted} = $path_to_comment;
        close COMMENT_FILE;
    }

    my @sorted_times = sort by_recent_time keys %most_recent_comments;

    foreach my $time_commented (@sorted_times){
        my $comment_dir = $most_recent_comments{$time_commented};
        open FILE_COMMENT, "<$comment_dir/comment.txt" or die "Unable to open comments file: $comment_dir/comment.txt";
        my $comment_details = join "", <FILE_COMMENT>;
        # set the html for the comment here
        open COMMENT_BOX, "<components/comment_box.html" or die "Unable to open file: components/comment_box.html";

        # get the details of the person who commented
        my $commenter_zid = get_from($comment_details);
        my $mates_full_name = zid_to_fullname($commenter_zid);
        my $comment_message = get_message($comment_details);
        my $profile_pic_path = get_profile_pic($commenter_zid);

		# replace zids with full names
		$comment_message = convert_zid_fullname_links($comment_message);

        # get all replies to that comment
        $replies_html = get_replies($comment_dir);

        # substitute all this information into a comment box
        my $path_for_replies = "$comment_dir/replies/";
        my $comment_id = "commnet_$comment_reply_id";
        @comments_html = <COMMENT_BOX>;
        $comments_html_joined = join "", @comments_html;
        $comments_html_joined =~ s/\{\{full_name\}\}/$mates_full_name/g;
        $comments_html_joined =~ s/\{\{comment\}\}/$comment_message/g;
        $comments_html_joined =~ s/\{\{date\}\}/$time_commented/g;
        $comments_html_joined =~ s/\{\{replies\}\}/$replies_html/g;
        $comments_html_joined =~ s/\{\{profile_pic\}\}/$profile_pic_path/g;
        $comments_html_joined =~ s/\{\{path_to_comment\}\}/$path_for_replies/g;
        $comments_html_joined =~ s/\{\{comment_id\}\}/$comment_id/g;
        $comments_html_joined =~ s/\{\{zid\}\}/$commenter_zid/g;

        # determine whether we need to display a close button
        # if the person who owns the post isn't the person who is logged in they should be able to delete
        # the post
        my $delete_button_html = "<button type=\"button\" class=\"close\" aria-hidden=\"true\" name=\"$comment_dir\" onclick=\"delete_post(this)\">&times;</button>";
        my $current_user = param("current_user") || param("username");
        if ($current_user eq $commenter_zid){
            $comments_html_joined =~ s/\{\{delete_button\}\}/$delete_button_html/g;
        }

        else{
            $comments_html_joined =~ s/\{\{delete_button\}\}//g;
        }

        $comment_reply_id++;

        # store the comment for the post
        push @all_comments, $comments_html_joined;

        close COMMENT_BOX;
        close FILE_COMMENT;
    }

    my $all_comments_html_string = join "\n", @all_comments;

    return <<eof;
$all_comments_html_string
eof
}

# return the replies to a comment
sub get_replies{
    my ($comments_dir) = @_;
    my @replies_paths = reverse sort(glob("$comments_dir/replies/*"));
    my $replies_html_string = "";
    my @replies_html = ();
    my @all_replies = ();
    my $mate_details = "";
    my %most_recent_replies = ();

    foreach my $reply_path (@replies_paths){
        open FILE_REPLY, "<$reply_path/reply.txt" or die "Unable to open replies file: $reply_path/reply.txt to store in hash";
        my $reply_details = join "", <FILE_REPLY>;
        my $time_of_reply = get_time($reply_details);
        $time_of_reply =~ s/\+\d*//g;
        $most_recent_replies{$time_of_reply} = $reply_path;
        close FILE_REPLY;
    }

    my @sorted_times = sort by_recent_time keys %most_recent_replies;

    foreach my $time_replied (@sorted_times){
        #print "REPLY PATH = $reply_path/user.txt\n\n";
        my $reply_path = $most_recent_replies{$time_replied};
        open FILE_REPLY, "<$reply_path/reply.txt" or die "Unable to open replies file: $reply_path/reply.txt";
        my $reply_details = join "", <FILE_REPLY>;
        # use same comment box
        open REPLY_BOX, "<components/comment_box.html" or die "Unable to open replies file";

        # get the html for the comment box
        @replies_html = <REPLY_BOX>;
        $replies_html_string = join "", @replies_html;

        # get the information of the mate that wrote the reply
        my $mate_zid = get_from($reply_details);
        my $full_name = zid_to_fullname($mate_zid);
        my $reply = get_message($reply_details);
        my $profile_pic_path = get_profile_pic($mate_zid);

		$reply = convert_zid_fullname_links($reply);

        # substitue all the information into the html
        my $path_for_replies = "$comments_dir/replies/";
        $replies_html_string =~ s/\{\{full_name\}\}/$full_name/g;
        $replies_html_string =~ s/\{\{comment\}\}/$reply/g;
        $replies_html_string =~ s/\{\{date\}\}/$time_replied/g;
        $replies_html_string =~ s/\{\{replies\}\}//g;
        $replies_html_string =~ s/\{\{profile_pic\}\}/$profile_pic_path/g;
        $replies_html_string =~ s/\{\{path_to_comment\}\}/$path_for_replies/g;
        $replies_html_string =~ s/\{\{comment_id\}\}/$comment_reply_id/g;
        $replies_html_string =~ s/\{\{zid\}\}/$mate_zid/g;

        # determine whether we need to display a close button
        # if the person who owns the post isn't the person who is logged in they should be able to delete
        # the post
        my $delete_button_html = "<button type=\"button\" class=\"close\" aria-hidden=\"true\" name=\"$reply_path\" onclick=\"delete_post(this)\">&times;</button>";
        my $current_user = param("current_user") || param("username");
        if ($current_user eq $mate_zid){
            $replies_html_string =~ s/\{\{delete_button\}\}/$delete_button_html/g;
        }

        else{
            $replies_html_string =~ s/\{\{delete_button\}\}//g;
        }

        $comment_reply_id++;

        push @all_replies, $replies_html_string;

        close REPLY_BOX;
        close FILE_REPLY;
    }

    my $all_replies_html = join "", @all_replies;
    return <<eof;
$all_replies_html
eof
}

#
# HTML placed at the bottom of every page
# It includes all supplied parameter values as a HTML comment
# if global variable $debug is set
#
sub page_trailer {
    my $html = "";
    $html .= join("", map("<!-- $_=".param($_)." -->\n", param())) if $debug;
    $html .= end_html;
    return $html;
}

# helper functions for getting user information
sub get_user_details{
    my ($path) = @_;
    open my $F, "<$path" or die "Unable to find user details: $path";
    my $details = join '', <$F>;
    close $F;
    return $details;
}

sub get_user_details_zid{
    my ($zID) = @_;
    open ZID_USER_DET, "<$users_dir/$zID/user.txt" or die "Unable to open user's details: $users_dir/$zID/user.txt";
    my $details = join '', <ZID_USER_DET>;
    close ZID_USER_DET;
    return $details;
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

sub get_program{
    my ($details) = @_;
    my $program = "";
    if ($details =~ /program\s*=\s*(.*)/){
        $program = $1;
    }
    return $program;
}

sub get_home{
    my ($details) = @_;
    my $home = "";
    if ($details =~ /home_suburb\s*=\s*(.*)/){
        $home = $1;
    }
    return $home;
}

sub get_birthday{
    my ($details) = @_;
    my $birthday = "";
    if ($details =~ /birthday\s*=\s*(.*)/){
        $birthday = $1;
    }
    return $birthday;
}

sub get_zid{
    my ($details) = @_;
    my $z = "";
    if ($details =~ /zid\s*=\s*(.*)/){
        $z = $1;
    }
    return $z;
}

# getters for fields in comments.txt
sub get_from{
    my ($details) = @_;
    my $from = "";
    if ($details =~ /from\s*=\s*(.*)/){
        $from = $1;
    }

    return $from;
}

sub get_message{
    my ($details) = @_;
    my $message = "";
    if ($details =~ /message\s*=\s*(.*)/){
        $message = $1;
    }

    return $message;
}

sub zid_to_fullname{
    my ($zid) = @_;
    my $details = get_user_details_zid($zid);
    my $full_name = get_full_name($details);
    return $full_name;
}

sub get_time{
    my ($details) = @_;
    my $time = "";
    if ($details =~ /time\s*=\s*(.*)/){
        $time = $1;
    }

    return $time;
}

# converts all ZIDS in a string into full names
sub convert_zid_fullname{
	my ($string) = @_;
	my @zids = $string =~ /(z[\d]{7})/g;
	foreach my $zid (@zids){
		my $mate_full_name = zid_to_fullname($zid);
		$string =~ s/$zid/$mate_full_name/;
	}

	return $string;
}

# similar to the above function except all the full names are also links in html
sub convert_zid_fullname_links{
	my ($string) = @_;
	my @zids = $string =~ /(z[\d]{7})/g;
	foreach my $zid (@zids){
		my $mate_full_name = "<button class=\"button-link-no-underline\" value=\"$zid\" onclick=\"mate_clicked(this)\">" . zid_to_fullname($zid) . "</button>";
		$string =~ s/$zid/$mate_full_name/;
	}

	return $string;
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

sub get_background{
    my ($user_zid) = @_;
    my $background_path = "$users_dir/$user_zid/background.jpg";
    if (!open(BACKGROUND, "<$background_path")){
        $background_path = ""; # put in some default background
    }

    return $background_path;
}

sub get_email_address{
    my ($details) = @_;
    my $email_addr = "";
    if ($details =~ /email\=(.*)/){
        $email_addr = $1;
    }

    return $email_addr;
}

# returns the privacy settings for a user
sub get_privacy{
    my ($details) = @_;
    my $privacy = "public";
    if ($details =~ /privacy=(.*)/){
        $privacy = $1;
    }

    return $privacy;
}

# returns a boolean to indicate whether a user is suspended
sub get_suspended{
    my ($details) = @_;
    my $suspended = "false";
    if ($details =~ /suspend=(.*)/){
        $suspended = $1;
    }

    return $suspended;
}

# gets "about me info about the user"
sub get_about_me{
    my ($details) = @_;
    my $about_me = "";
    if ($details =~ /about=(.*)/){
        $about_me = $1;
    }

    return $about_me;
}

# gets the courses that the user takes
sub get_courses{
    my ($details) = @_;
    my $courses = "";
    if ($details =~ /courses=\[(.*)\]/){
        $courses = $1;
    }

    return $courses;
}

# checks if a user is registered
sub is_registered{
    my ($zid) = @_;
    my $registered = 0; # assume false, prove true
    open REGISTRATION, "<confirm_requests.txt" or die "Unable to open file containing pending requests";
    my $registration_details = join "", <REGISTRATION>;
    if ($registration_details !~ /$zid/){
        $registered = 1;
    }
    close REGISTRATION;

    return $registered;
}

# stores the updated user details
sub store_user_details{
    my ($zid, $user_details) = @_;
    open my $ZID_USER_DET, ">$users_dir/$zid/user.txt" or die "Unable to open user details: $users_dir/$zid/user.txt to store new friends";
    print $ZID_USER_DET $user_details;
    close $ZID_USER_DET;
}

# compares two dates to sort a list or hash where the keys are the dates
# ends up sorting by the most recent time
sub by_recent_time{
    # a and b are automatically passed in

    # remove the time zones
    #$a =~ s/\+\d*//g;
    #$b =~ s/\+\d*//g;

    # create date time objects
    my $dt_a = DateTime::Format::ISO8601->parse_datetime( $a );
    my $dt_b = DateTime::Format::ISO8601->parse_datetime( $b );

    # compare them
    my $diff = DateTime->compare($dt_b, $dt_a);
    return $diff;
}
