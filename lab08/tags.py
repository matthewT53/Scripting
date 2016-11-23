#!/usr/local/bin/python3.5
import sys
import subprocess
import re
from collections import defaultdict

# create a hash table to hold the data about the tags
tagsDict = defaultdict(dict)
orderOfFreq = False

argList = sys.argv;
for arg in argList:
    if arg == "-f":
        orderOfFreq = True
    else:
        url = arg

if len(argList) != 2 and len(argList) != 3:
    sys.exit("Usage: ./tags.py <url> [-f]")

regexTags = r"< *([a-zA-Z]+[0-9]*) *" # THIS doesn't allow us to extract all tags from a line as there
# may be more than one tag on the line
regexComments = r"<!--.*-->\n"

# fetch the webpage
webpage = subprocess.check_output(["wget", "-q", "-O-", url], universal_newlines=True)
# ignore html comments
webpage = re.sub(regexComments, "", webpage)
# create an array where each element is a line of the webpage
webpageData = re.split(r"\n", webpage)

# traverse through each line of the webpage
for line in webpageData:
    # find all html tags
    tagMatches = re.findall(regexTags, line)
    if tagMatches:
        # loop through all the tags and update the hash table
        for tag in tagMatches:
            tag = tag.lower() # convert the tag to lover case
            if not tag in tagsDict:
                tagsDict[tag] = 1
            else:
                tagsDict[tag] += 1

# print the number of occurences of each tag
if orderOfFreq == True:
    keys = sorted(tagsDict.keys(), key=lambda k: tagsDict[k])
else:
    keys = sorted(tagsDict.keys())

for tag in keys:
    print (tag, tagsDict[tag])
