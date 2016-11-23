#!/usr/bin/python
import sys
import re
newlineRegex = r"\n"
maxLines = 10
argumentList = sys.argv; # get the list of all the arguments
i = 1
for i in range(1, len(argumentList)):
    #print i
    fileHandle = open(argumentList[i], "r")

    # read the lines of the file into a list
    lines = fileHandle.readlines()

    # determine whether the file has 10 lines to print
    if maxLines > len(lines):
        start = 0
    else:
        start = len(lines) - maxLines

    # print the lines
    for j in range(start, len(lines)):
        print re.sub(newlineRegex, "", lines[j], 1);

    fileHandle.close()
