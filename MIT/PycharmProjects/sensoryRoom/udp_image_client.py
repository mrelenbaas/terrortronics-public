#!/usr/bin/env python

import os
import random
import socket, select
from time import gmtime, strftime, sleep
from random import randint

#image = "tux.png"
FILENAME = 'image_to_process_'
EXTENSION = '.png'

HOST = '192.168.0.0'
PORT = 5005

#sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#server_address = (HOST, PORT)
#sock.connect(server_address)

#image_to_process_0

counter = 0


class SomeClass():
    
    def __init__(self):
        print('CONSTRUCTOR')
        
    def some_function(self, image):
        try:
            print('image: ' + image)
            myfile = open(image, 'rb')
            bytes = myfile.read()
            size = len(bytes)
            print('size: ' + str(size))

            #max_size = 9216
            max_size = 1024
            packet_count = int(size / max_size) + 1
            print('packet count: ' + str(packet_count))

            sock = socket.socket(
                socket.AF_INET,
                socket.SOCK_DGRAM,
                socket.IPPROTO_UDP)
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
            sock.settimeout(0.2)
            #sock.bind('', 5005)
            #sock.sendto(b'start', (HOST, PORT))
            for i in range(packet_count):
                print('i: ' + str(i))
                start = i * max_size
                if i < packet_count - 1:
                    end = (i + 1) * max_size
                    print('full: ' + str(start) + ' / ' + str(size))
                    print(str(bytes)[start:end])
                    sock.sendto(bytes[start:end], ('<broadcast>', PORT))
                else:
                    print('partial: ' + str(start) + ' / ' + str(size))
                    print(str(bytes)[start:size])
                    sock.sendto(bytes[start:size], ('<broadcast>', PORT))
                #sleep(0.2)
            final_message = 'END' + image.split('_')[-1]
            print('final_message: ' + final_message)
            sock.sendto(b'END', (HOST, PORT))
            #sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            #sock.sendto(bytes, (HOST, PORT))
            
            myfile.close()
        finally:
            sock.close()

if __name__ == '__main__':
    someClass = SomeClass()
    while(True):
        desktop = os.path.expanduser("~/Desktop")
        filenames = next(os.walk(desktop), (None, None, []))[2]  # [] if no file
        for filename in filenames:
            if FILENAME in filename:
                print('Found filename: ' + filename)
                someClass.some_function(desktop + '/' + filename)
                os.remove(os.path.expanduser("~/Desktop") + '/' + filename)
        
        sleep(1)
        print(counter)
        counter += 1
    print('complete')
