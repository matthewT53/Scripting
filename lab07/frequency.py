#!/usr/bin/python
import sys
import re
import glob

# FUNCTION DEFINITIONS
def findWordFrequency(totalWords, totalWordMatches):
    return float(totalWordMatches) / float(totalWords)

def findTotal(filename):
    fileHandle = open(filename, 'r') # open file for reading
    total = 0
    for line in fileHandle:
        words = re.split("[^a-zA-Z]", line)
        for word in words:
            if not word == "":
                total += 1

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
    return total
# MAIN PROGRAM
wordToMatch = sys.argv[1] # word to search for

# iterate through all the files
for file in sorted(glob.glob("poems/*.txt")):
    totalWords = findTotal(file)
    totalWordMatches = findWordMatches(file, wordToMatch)
    freq = findWordFrequency(totalWords, totalWordMatches)
    author = file
    author = re.sub(r".txt", "", author)
    author = re.sub(r"_", " ", author)
    author = re.sub(r"poems/", "", author)
    print ("%4d/%6d = %.9f %s" % (totalWordMatches, totalWords, freq, author))
