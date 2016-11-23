#!/usr/bin/python3.5

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind(('', 4580))

s.listen(5)
(clientsocket, address) = s.accept()
while True:
    print ("Address: " + address[0] + " Port: " + str(address[1]))
    data = clientsocket.recv(1024).decode()
    print (data)
s.close()
