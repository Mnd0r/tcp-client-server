#!/usr/bin/env python3

import socket
import time

HOST = ''  # Standard loopback interface address (localhost)
PORT = 3001        # Port to listen on (non-privileged ports are > 1023)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    while True:
        print('----->Server is waiting')
        s.listen()
        connection, address = s.accept()
        if connection is not None:
            break

    with connection:
        print('----->Server Connected by', address)
        while True:
            data = connection.recv(1024)
            if data is not None and data is not "":
                formattedData = int(data, 2)
                print('----->binary base-2 received', data)
                print('----->converted received', formattedData)
            time.sleep(5)
