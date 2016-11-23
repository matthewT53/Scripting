#!/usr/bin/perl -w
# hashing module for sha-256
use Digest::SHA qw(sha256_hex);

print "Setting up the dataset...\n";
$dataset_dir = "dataset-medium";
@dataset_users = sort(glob("$dataset_dir/*"));

# traverse through the directories of all the users
foreach $user_path (@dataset_users){
    print "Modifying user.txt of $user_path\n";
    open USER_INFO, "<$user_path/user.txt" or die "Unable to open: $user_path/user.txt for reading";
    $user_data = join "", <USER_INFO>;
    close USER_INFO;

    # hash the password
    my $hashed_password = "";
    if ($user_data =~ /password=(.*)/){
        $hashed_password = sha256_hex($1);
        $user_data =~ s/password=.*/password=$hashed_password/g;
    }

    # append privacy and other settings to the user file
    open USER_INFO, ">$user_path/user.txt" or die "Unable to open: $user_path/user.txt";
    $user_data .= "privacy=public\n";
    $user_data .= "suspend=false\n";
    $user_data .= "about=";
    print USER_INFO $user_data;
    close USER_INFO;
}
print "Finished setting up.\n";
