#!/usr/bin/python
import sys
import re

total = 0
for line in sys.stdin:
    words = re.split("[^a-zA-Z]", line)
    for word in words:
        if not word == "":
            total += 1

print ("%d words" % total)
