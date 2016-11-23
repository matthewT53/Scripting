#!/usr/bin/python
import sys
import re
import glob
import math
from collections import defaultdict

# FUNCTION DEFINITIONS
def findWordFrequencyLog(file, wordToMatch):
    totalWords = findTotal(file)
    totalWordMatches = findWordMatches(file, wordToMatch) + 1
    freq = float(totalWordMatches) / float(totalWords)
    return math.log(freq)

def findTotal(filename):
    fileHandle = open(filename, 'r') # open file for reading
    total = 0
    for line in fileHandle:
        words = re.split(r"[^a-zA-Z]", line)
        for word in words:
            if not word == "":
                total += 1
    fileHandle.close()
    return total

def findWordMatches(filename, wordToMatch):
    total = 0
    fileHandle = open(filename, 'r')
    wordToMatch = wordToMatch.lower()
    for line in fileHandle:
        words = re.split(r"[^a-zA-Z]", line)
        for word in words:
            word = word.lower()
            if word == wordToMatch:
                total += 1
    fileHandle.close()
    return total

# MAIN program
# 2-D hash to hold the log sums for each poem
logSums = defaultdict(dict)
# process all the arguments
argList = sys.argv;
poems = [] # empty list
debug = 0 # debug flag to indicate whether debugging should be turned on
i = 0
for arg in argList:
    if arg == "-d":
        debug = 1
    else:
        poems.append(arg) # assume every other argument is a filename
        i += 1

# print (poems[1:])

# determine who wrote which poem
for poem in poems[1:]:
    for file in sorted(glob.glob("poems/*.txt")):
        # open the file each time it needs to be compared to a file in poems/
        fileHandle = open(poem, 'r')
        author = re.sub(r".txt", "", file)
        author = re.sub(r"_", " ", author)
        author = re.sub(r"poems/", "", author)
        for line in fileHandle:
            words = re.split(r"[^a-zA-Z]", line)
            #print (words)
            for word in words:
                if not word == "":
                    logProb = findWordFrequencyLog(file, word)
                    #print ("word = %s and logProb = %.4f" % (word, logProb))
                    if not author in logSums.get(poem, {}):
                        #print ("First time")
                        logSums[poem][author] = logProb
                    else:
                        #print ("Other time")
                        logSums[poem][author] += logProb

        fileHandle.close()
        if debug == 1:
            print ("%s: log probability of %.1f for %s" % (poem, logSums[poem][author], author))

# print out the results
for poem in sorted(logSums.keys()):
    values = sorted(logSums[poem], key=lambda k: logSums[poem][k], reverse=True)
    print ("%s most resembles the work of %s (log-probability=%.1f)" % (poem, values[0], logSums[poem][values[0]]))
