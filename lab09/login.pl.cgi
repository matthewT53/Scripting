#!/usr/bin/perl -w

use CGI qw/:all/;
use CGI::Carp qw/fatalsToBrowser warningsToBrowser/;

# Basically just looked this up
# http://stackoverflow.com/questions/4853948/how-can-i-tell-if-a-perl-script-# is-executing-in-cgi-context
my $isCGI = defined($ENV{'GATEWAY_INTERFACE'});

if ($isCGI == 1){
	print header, start_html('Login');
	warningsToBrowser(1);

	$username = param('username') || '';
	$password = param('password') || '';

	#print "Start User: $username and Pass: $password\n";

	if ($username && $password) {
		# check if the user exists
		# my ($username, $password) = @_;
		if (!open(userFile, "accounts/$username/password")){
			print "Unknown username!\n";
		}

		else{
			my $correct_password = <userFile>;
			chomp $correct_password;
			# check if the password entered is correct
			if ($password eq $correct_password){
				print "$username authenticated.\n";
			}

			else{
				print "Incorrect password!\n";
			}
		}
	}

	elsif ($username && !$password){
		print start_form, "\n";
		param("username", $username);
		print hidden('username'),"\n";
		print "Password:\n", textfield('password'), "\n";
		print submit(value => Login), "\n";
		print end_form, "\n";
	}

	elsif (!$username && $password){
		print start_form, "\n";
		param("password", $password);
		print hidden('password'),"\n";
		print "Username:\n", textfield('username'), "\n";
		print submit(value => Login), "\n";
		print end_form, "\n";
	}

	else {
		print start_form, "\n";
		print "My login screen:\n";
		print "Username:\n", textfield('username'), "\n";
		print "Password:\n", textfield('password'), "\n";
		print submit(value => Login), "\n";
		print end_form, "\n";
	}


	print end_html;
	exit(0);
}

else{
	print "username: ";
	$username = <STDIN>;
	chomp $username;
	print "password: ";
	$password = <STDIN>;
	chomp $password;

	# sanitize the usernamhttp://stackoverflow.com/questions/4853948/how-can-i-tell-if-a-perl-script-is-executing-in-cgi-contexte
	$username = substr $username, 0, 256;

	$password_file = "accounts/$username/password";
	if (!open F, "<$password_file"){
		print "Unknown username!\n";
	}

	else{
		$correct_password = <F>;
		chomp $correct_password;
		if ($password eq $correct_password){
		    print "You are authenticated.\n";
		}

		else{
		    print "Incorrect password\n";
		}
	}
}
