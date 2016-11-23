#!/usr/bin/python3.5

import sys
import re
import fileinput

regex = r"[\d]{8}"
phone_numbers = []

for line in fileinput.input():
    match = re.findall(regex, line)
    if match:
        for phone_num in match:
            phone_numbers.append(phone_num)

for num in phone_numbers:
    print(num)
