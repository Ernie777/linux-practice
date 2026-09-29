# -*- coding: utf-8 -*-
import socket
import time

HOST = '127.0.0.1'
PORT = 2000

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

while True:
    outdata = input()
    if outdata == "quit":
        break

    s.send(outdata.encode())
    print('send: ' + outdata)
    
    indata = s.recv(1024)
    print('recv: ' + indata.decode())

    time.sleep(1)
s.close()
print('close connection')