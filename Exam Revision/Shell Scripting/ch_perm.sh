#!/bin/sh

# Developed by: Matthew Ta
# Description: This utility recursively changes the permissions of all files and folders of a given directory
# Usage: ./ch_perm.sh <Directory or file> <New Permission> [Optional arguments]
# Optional arguments:
# -v (--verbose): Verbose output shows debugging information
# doesn't work if directory and files have whitespaces (fix: use find)
# Would have been useful for assignment 2 :P

# Notes on shell functions
# Variables in the function have no scope
# local enforces local scope to variables
directory_to_traverse (){
    local directory_to_traverse=$1

    # permissions such as 644 prevent this utility from
    # further modifying the folder / file permission settings
    # temporarily remove permissions to access directory
    sudo chmod 0755 "$directory_to_traverse"
    if [ -d "$directory_to_traverse" ]
    then
        # go into the directory
        cd "$directory_to_traverse"

        # check if the this script should chmod hidden files too
        if test $hidden -eq 1
        then
            more_directories=`ls -a`
            # remove the . and .. which make this script infinitely loop
            more_directories=`echo "$more_directories" | sed "s/^\.$//g"`
            more_directories=`echo "$more_directories" | sed "s/^\.\.$//g"`
        else
            more_directories=`ls`
        fi

        # loop through all folders and files in the directory
        for current_dir in $more_directories
        do
            local this_dir=$current_dir
            directory_to_traverse "$this_dir"
            if test $debug_output -eq 1
            then
                echo "Chmod: $this_dir with $permissions permissions"
            fi
            sudo chmod $permissions "$this_dir"
        done

        # step out of the directory
        cd ..
    fi

    # change the permissions of the file or folder
    sudo chmod $permissions "$directory_to_traverse"
}

# ================================= MAIN PROGRAM STARTS HERE ===============================
directory=$1
permissions=$2
debug_output=0
hidden=0

# check the correct number of arguments is provided
if test $# -lt 2
then
    echo "\nThis program recursively changes the permissions of all files and folders in a specified directory\n"
    echo "Usage: ./ch_perm.sh <directory or filename> <new permissions>\n"
    echo "Needs to be run with sudo\n"
    echo "Optional arguments: \n"
    printf "\t%-10s%-20s%-20s\n" "-v" "--verbose" "Verbose output (recommended)"
    printf "\t%-10s%-20s%-40s\n" "-x" "--hidden" "Apply to hidden files and folders"
    printf "\t%-10s%-20s%-20s\n" "-h" "--help" "Help"
    exit 1
fi

# process the arguments
for argument in "$@"
do
    # test whether the verbose flag has been given
    if [ "$argument" = "--verbose" -o "$argument" = "-v" ]
    then
        debug_output=1
    fi

    # test whether the hidden flag was set
    if [ "$argument" = "--hidden" -o "$argument" = "-x" ]
    then
        hidden=1
    fi

    # test whether the help flag has been specified
    if [ "$argument" = "--help" -o "$argument" = "-h" ]
    then
        echo "\nThis program recursively changes the permissions of all files and folders in a specified directory\n"
        echo "Usage: ./ch_perm.sh <directory or filename> <new permissions>\n"
        echo "Needs to be run with sudo\n"
        echo "Optional arguments: \n"
        printf "\t%-10s%-20s%-20s\n" "-v" "--verbose" "Verbose output (recommended)"
        printf "\t%-10s%-20s%-40s\n" "-x" "--hidden" "Apply to hidden files and folders"
        printf "\t%-10s%-20s%-20s\n" "-h" "--help" "Help"
        exit 1
    fi
done

# start iterating through the directory
directory_to_traverse $directory
