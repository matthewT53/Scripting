#!/usr/bin/python
import sys
import re
argList = sys.argv
wordToMatch = argList[1];
total = 0

wordToMatch = wordToMatch.lower()
for line in sys.stdin:
    words = re.split(r"[^a-zA-Z]", line)
    for word in words:
        word = word.lower()
        if word == wordToMatch:
            total += 1

print ("%s occurred %d times" % (wordToMatch, total))
