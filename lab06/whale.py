#!/usr/bin/python
import fileinput
import re
import sys

argList = sys.argv # get all arguments as a list
species = argList[1] # get the species of the whale
inputReg = r"(\d+)\s+(.+)"
pods = 0
individuals = 0

for line in sys.stdin:
    if re.search(inputReg, line):
        match = re.search(inputReg, line)
        numWhales = match.group(1)
        whaleType = match.group(2)
        if whaleType == species:
            pods += 1
            individuals += int(numWhales)

print "%s observations: %d pods, %d individuals" % (species, pods, individuals)
