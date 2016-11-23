#!/usr/bin/python3.5

import socket
import sys
import fileinput

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('', 4580))
while True:
    message = input("Enter message: ")
    s.send(message.encode())
s.close()
