#!/bin/sh

string="artist | (artist)"
string2="sdfsdfsdfsd fsfsd sdvxc"
pattern="\|"

if [[ $string =~ $pattern ]]; # if using bash
then
    echo "You git it kid"
else
    echo "You didn't do it right"
fi

# below if a method for comparing using regex and works for most shells
if echo "$string" | egrep "\|" > /dev/null
then
    echo "Sh is ok"
else
    echo "Internet lied to me"
fi
