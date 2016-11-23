#!/bin/sh
IFS=abc
# only first character of IFS is used to alter the output of $*
# $* may look the same as $@ but they are different
echo "$*"
echo "$@"
