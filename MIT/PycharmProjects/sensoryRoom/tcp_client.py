'''
import socket

FILENAME = 'image_to_process_'
EXTENSION = '.png'

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect(('192.168.0.47', 5005)) # Connect
    sock.sendall(bytes(data + "\n", "utf-8")) # Send data
    received = str(sock.recv(1024), "utf-8") # Receive data synchronically

print('complete')
'''

#!/usr/bin/env python

import os
import random
import socket, select
from time import gmtime, strftime, sleep
from random import randint

#image = "tux.png"
FILENAME = 'image_to_process_'
OTHER_FILENAME = 'previous_pingtest.txt'
FILENAME_MAC = 'hosts.txt'
EXTENSION = '.png'

#HOST = '192.168.1.2'
hosts = []
PORT = 5005

counter = 0
currentFilename = b''

is_windows_discovery = False
if os.name != 'posix':
    print('windows found')
    is_windows_discovery = True
else:
    print('posix found')


class SomeClass():
    
    def __init__(self):
        print('CONSTRUCTOR')
        
    def some_function(self, image, host):
        try:
            print('image: ' + image)
            myfile = open(image, 'rb')
            bytesToSend = myfile.read()
            size = len(bytesToSend)
            print('size: ' + str(size))

            max_size = 1024
            packet_count = int(size / max_size) + 1
            print('packet count: ' + str(packet_count))

            for i in range(packet_count):
                start = i * max_size
                end = (i + 1) * max_size
                print('{}: {}:{}'.format(i, start, end))
                if i < packet_count - 1:
                    with socket.socket(
                            socket.AF_INET,
                            socket.SOCK_STREAM) as sock:
                        sock.connect((host, 5005)) # Connect
                        sock.sendall(bytesToSend[start:end]) # Send data
                        sock.close()
                else:
                    with socket.socket(
                            socket.AF_INET,
                            socket.SOCK_STREAM) as sock:
                        sock.connect((host, 5005)) # Connect
                        sock.sendall(bytesToSend[start:]) # Send data
                        sock.close()
            with socket.socket(
                    socket.AF_INET,
                    socket.SOCK_STREAM) as sock:
                sock.connect((host, 5005)) # Connect
                sock.sendall(currentFilename) # Send data
                sock.close()
        except:
            myfile.close()
            sock.close()
        finally:
            sock.close()

    def some_function_windows_discovery(self, image, host):
        try:
            print('---')
            print('host: ' + host)
            print('image: ' + image)
            myfile = open(image, 'rb')
            bytesToSend = myfile.read()
            size = len(bytesToSend)
            print(bytesToSend)
            print('size: ' + str(size))

            max_size = 1024
            packet_count = int(size / max_size) + 1
            print('packet count: ' + str(packet_count))

            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
                #sock.settimeout(time.time() + 5.0)
                sock.connect((host, 5005)) # Connect
                sock.send(bytesToSend) # Send data
                sock.close()
        except:
            myfile.close()
            sock.close()
        finally:
            sock.close()

if __name__ == '__main__':
    someClass = SomeClass()
    is_running = True
    while(is_running):
        if is_windows_discovery:
            desktop = os.path.expanduser('~/Desktop')
            if socket.gethostname() == 'DESKTOP-CR5GQ2G':
                desktop = os.path.expanduser("~\OneDrive\Desktop")
            filenames = next(os.walk(desktop), (None, None, []))[2]
            for filename in filenames:
                #//print(desktop + '\filename: ' + filename)
                if OTHER_FILENAME in filename:
                    currentFilename = filename.encode('ascii')
                    print('Found filename: ' + filename)
                    path = '' + desktop + '\\' + filename
                    print('path: ' + path)
                    with open(path) as file:
                        while line := file.readline():
                            clean_line = line.rstrip()
                            clean_line = clean_line.split('Reply from ')[-1]
                            clean_line = clean_line.split(':')[0]
                            hosts.append(clean_line)
                            print('hosts: ' + hosts[-1])
                    for host in hosts:
                        someClass.some_function_windows_discovery(
                            desktop + '/' + filename,
                            host)
                    os.remove(
                        os.path.expanduser(desktop) + '/' + filename)
                    is_running = False
        else:
            desktop = os.path.expanduser("~/Desktop")
            filenames = next(os.walk(desktop), (None, None, []))[2]
            for filename in filenames:
                if FILENAME in filename:
                    currentFilename = filename.encode('ascii')
                    print('Found filename: ' + filename)
                    host_filename = '' + desktop + '/' + FILENAME_MAC
                    with open(host_filename) as file:
                        while line := file.readline():
                            clean_line = line.rstrip()
                            print(clean_line)
                            clean_line = clean_line.split('Reply from ')[-1]
                            print(clean_line)
                            clean_line = clean_line.split(':')[0]
                            print(clean_line)
                            hosts.append(clean_line)
                            print('hosts: ' + hosts[-1])
                    for host in hosts:
                        print('host: ' + host)
                        someClass.some_function(desktop + '/' + filename, host)
                    os.remove(os.path.expanduser("~/Desktop") + '/' + filename)

        sleep(1)
        print(counter)
        counter += 1
    print('complete')

