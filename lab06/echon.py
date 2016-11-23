#!/usr/bin/python
import sys
import re

# Demonstrate traversing through arguments
# for arg in sys.argv:
#    print arg

argumentList = sys.argv
#print argumentList
#print len(argumentList)
# check if the user supplied the correct number of arguments
if len(argumentList) != 3:
    sys.exit("Usage: ./echon.py <number of repetitions> <string to repeat>")

maxIterations = argumentList[1];
string = argumentList[2];

# check to see if maxIterations is actually a number
isNumRegex = r"^[0-9]+$"
if not (re.search(isNumRegex, maxIterations)):
    sys.exit("./echon.py: Argument 1 must be a non-negative integer")

i = 0
while i < int(maxIterations):
    print string
    i += 1


# print "Max Iterations = %d and string to print is: %s" %( int(maxIterations), string )
