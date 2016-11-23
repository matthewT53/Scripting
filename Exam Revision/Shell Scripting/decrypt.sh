#!/bin/sh

# Author: Mr Matthew
# Description: Decrypts given directories and files
# Made just for fun to study for COMP2041 exam

# decrypt the file
decrypt_directory (){
    local directory_to_decrypt=$1
    local password=$2

    # loop through the directory
    # this method of looping deals with whitespaces in folder and file names
    find "$directory_to_decrypt" | while read current_dir
    do
        if [ -f "$current_dir" ]
        then
            # echo "Currnet dir: $current_dir"
            file="$current_dir"
            file_nogpg=`echo "$file" | dos2unix | sed "s/\.gpg$//g"`
            echo "$password" | gpg2 --batch --passphrase-fd 0 -d "$file" > "$file_nogpg" 2>/dev/null
            gpg_ret_val=$?

            # check for errors with GPG
            if test $gpg_ret_val -eq 0
            then
                echo "Decrypted: $file successfully."
                rm "$file"
            else
                echo "Failed to decrypt: $file"
                rm "$file_nogpg"
            fi
        else
            echo "Not a file: $current_dir"
        fi
    done
}

explore_directories (){
    local password_decrypt=$1
    SAVE_IFS=$IFS
    IFS=''
    cat "conf.enc" | while read dir
    do
        decrypt_directory "$dir" "$password_decrypt"
    done
    IFS=$SAVE_IFS
}


# =================== Main program starts here =================================
hidden=0

for arg in $@
do
    if [ "$arg" = "-h" -o "$arg" = "--help" ]
    then
        echo "This script uses GPG to decrypt all the directories specified in conf.enc"
        echo "Please run conf.sh first to configure conf.enc"
        echo "Optional arguments: \n"
        printf "\t%-10s%-20s%-40s\n" "-x" "--hidden" "Decrypt hidden files"
        printf "\t%-10s%-20s%-20s\n" "-h" "--help" "Help"
        exit 0
    else
        echo "Invalid Argument"
        exit 1
    fi
done

# get the password to decrypt
echo "Enter password: "
stty -echo
read password
stty echo

explore_directories "$password"
