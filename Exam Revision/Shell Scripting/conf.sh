#!/bin/sh

# Author: Mr Matthew
# Description: Receives a bunch of directories to be encrypted
# This file is for configuration and shouldn't be run often
# creates a conf called conf.enc that encrypt.sh uses to encrypt directories
# Don't worry conf.enc is encrypted too
# Disclaimer: This is prob not secure and I made this just for fun to study for COMP2041 exam

echo "Directories to encrypt (Control-D to stop):"
i=0
while read line
do
    if test $i -eq 0
    then
        echo "$line" > "conf.enc"
        i=1
    else
        #echo "$line"
        echo "$line" >> "conf.enc"
    fi
done
