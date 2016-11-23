#!/usr/bin/python
import fileinput # import library for input from STDIN
import re # import the regular expression library

regexLess5 = r"([0-4])"
regexGreat5 =r"([6-9])"
newline = r"\n"

for line in fileinput.input(): # this reads command line arguments as well
    filteredString = re.sub(regexLess5, "<", line, 0);
    filteredString = re.sub(regexGreat5, ">", filteredString, 0);
    filteredString = re.sub(newline, "", filteredString, 1);
    print filteredString
