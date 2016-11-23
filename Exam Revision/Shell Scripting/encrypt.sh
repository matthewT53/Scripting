#!/bin/sh

# Author: Mr Matthew
# Description: Encrypts a directory and all the files in it
# This was made just for fun to study for COMP2041 exam

encrypt_directory (){
    local directory_to_encrypt=$1
    local password=$2

    # loop through the directory
    # this method of looping deals with whitespaces in folder and file names
    find "$directory_to_encrypt" | while read current_dir
    do
        if [ -f "$current_dir" ]
        then
            file="$current_dir"
            echo "Encrypting: $file"
            echo "$password" | gpg2 --batch --passphrase-fd 0 -c "$file" 2>/dev/null
            # remove the plain text file
            rm "$file"
        else
            echo "Not a file: $current_dir"
        fi
    done
}

explore_directories (){
    local password_encrypt=$1
    SAVE_IFS=$IFS
    IFS=''
    cat "conf.enc" | while read dir
    do
        encrypt_directory "$dir" "$password_encrypt"
    done
    IFS=$SAVE_IFS
}

# ====================== Main program starts here =======================
hidden=0

for arg in $@
do
    if [ "$arg" = "-h" -o "$arg" = "--help" ]
    then
        echo "This script uses GPG to encrypt all the directories specified in conf.enc"
        echo "Please run conf.sh first to configure conf.enc"
        echo "Optional arguments: \n"
        printf "\t%-10s%-20s%-40s\n" "-x" "--hidden" "Encrypt hidden files"
        printf "\t%-10s%-20s%-20s\n" "-h" "--help" "Help"
        exit 0
    else
        echo "Invalid Argument"
        exit 1
    fi
done

echo "Enter password: "
stty -echo
read password
stty echo
echo "Confirm password: "
stty -echo
read confirm_pw
stty echo

# check if passwords are equal
if [ "$password" = "$confirm_pw" ]
then
    explore_directories "$password"
else
    echo "Passwords do not match!"
fi
