#!/usr/bin/python
import sys
import re
import string

# create two empty dictionarys (hash table)
whalePods = {}
whaleIndividuals = {}

inputRegex = r"(\d+)\s+(.+)" # the r is for raw string
# read from standard input
for line in sys.stdin:
    match = re.search(inputRegex, line)
    if match:
        # extract the num of individuals and whale type
        numberIndividuals = match.group(1)
        whaleType = match.group(2)

        whaleType = whaleType.lower() # convert whaleType to lowercase
        #print whaleType
        whaleType = re.sub(r"s$", "", whaleType) # remove plurals
        whaleType = re.sub(r"\s+", " ", whaleType) # remove middle spaces
        whaleType = re.sub(r"\s+$", "", whaleType) # remove trailing spaces
        # update the number of pods for the whalePods
        if not whalePods.has_key(whaleType):
            whalePods[whaleType] = 1
        else:
            whalePods[whaleType] += 1

        # update the number of individuals
        if not whaleIndividuals.has_key(whaleType):
            whaleIndividuals[whaleType] = int(numberIndividuals)
        else:
            whaleIndividuals[whaleType] += int(numberIndividuals)

# display the results
for key in sorted(whalePods.keys()): # number of keys in both hash tables should be the same
    print "%s observations: %d pods, %d individuals" % (key, int(whalePods[key]), int(whaleIndividuals[key]))
