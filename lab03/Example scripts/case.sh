#!/bin/sh
# Don't run this
for uppercase_filename in *
do
	lowercase_filename=`echo $uppercase_filename|tr A-Z a-z`
	if test "$lowercase_filename" = "$uppercase_filename"
	then
		continue
	fi

	if test -e "$lowercase_filename"
	then
		echo "$lowercase_filename already exists"
		continue
	fi
	mv "$uppercase_filename" "$lowercase_filename"
done

# double quotations to avoid lines with spaces being treated as numerous arguments
