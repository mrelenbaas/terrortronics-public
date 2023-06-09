#!/usr/bin/env python

import argparse
import os
import platform
import random
import socket, select
from time import gmtime, strftime, sleep
from random import randint

import urllib.request
import io
import binascii

FILENAME = 'image_to_process_'
EXTENSION = '.png'

HOST = '192.168.0.255'
PORT = 5005

is_discovery_complete = False
if os.name != 'posix':
    print('windows found')
    #is_discovery_complete = True
else:
    print('posix found')
path = os.path.normpath(os.path.expanduser('~/Desktop'))
print(socket.gethostname())
if socket.gethostname() == 'DESKTOP-CR5GQ2G':
    print('OneDrive Found')
    path = os.path.normpath(os.path.expanduser('~/OneDrive/Desktop'))
print('path found: ' + path)
if os.name == 'posix' and socket.gethostname() == 'raspberrypi':
    print('Pi found')
    print(os.path.normpath(
        os.path.expanduser('~/Apps/purebasic_demo/examples/3d/Data/Textures')))
    path = os.path.normpath(
        os.path.expanduser('~/Apps/purebasic_demo/examples/3d/Data/Textures'))

counter = 0

parser = argparse.ArgumentParser(
    prog='ProgramName',
    description='What the program does',
    epilog='Text at the bottom of help')
#parser.add_argument('filename')           # positional argument
#parser.add_argument('-c', '--count')      # option that takes a value
parser.add_argument('-d', '--discovery',
                    action='store_true')  # on/off flag
args = parser.parse_args()
print(args.discovery)
#if args.discovery == False:
#    is_discovery_complete = True
print('hostname: ' + socket.gethostname())
if os.name != 'posix':
    print('windows found')
    is_discovery_complete = True
elif socket.gethostname() == 'raspberrypi':
    print('Pi found')
    is_discovery_complete = True
else:
    print('Mac found')
print('path: ' + path)

if __name__ == '__main__':
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('', PORT))
    sock.listen(5)
    max_size = 170418
    total_data = b''
    total_size = 0
    socket_size = 9216
    while(True):
        if is_discovery_complete:
            print('DISCOVERY COMPLETE... WAITINGFOR IMAGES')
            data, addr = sock.accept()
            print(addr)
            print(data)

            binary_data = data.recv(1024)
            try:
                decoded_data = binary_data.decode('ascii')

                if 'Reply from ' in decoded_data:
                    continue
                
                print('{}'.format(decoded_data))
                
                randomInt = decoded_data
                randomInt = randomInt.split('.')[0]
                randomInt = randomInt.split('_')[-1]
                print('decoded_data: ' + decoded_data)
                print('randomInt: ' + str(randomInt))
                #isPosix = True if os.name == 'posix' else False
                #isPi = True if socket.gethostname() == 'raspberrypi' else False
                if (os.name == 'posix') and (socket.gethostname() == 'raspberrypi'):
                    print('IS PI')
                    filename_to_write = r'Cloud00' + randomInt + '.png'
                    final_path = os.path.join(path, filename_to_write)
                    print('PATH: ' + path)
                    print('FILENAME_TO_WRITE: ' + filename_to_write)
                    print('FINAL PATH: ' + final_path)
                    with open(final_path, 'w+b') as binary_file:
                        binary_file.write(total_data)
                        data.close()
                else:
                    print('IS WINDOWS')
                    print('path: ' + path)
                    p = '' + \
                        path + \
                        r'\PureBasic\Examples\3D\Data\Textures\Cloud00' + \
                        randomInt + \
                        '.png'
                    #p = os.path.join(
                    #    path,
                    #    r'\PureBasic\Examples\3D\Data\Textures\Cloud00' +
                    #    randomInt +
                    #    '.png')
                    print('p: ' + p)
                    with open(p, 'w+b') as binary_file:
                        binary_file.write(total_data)
                        data.close()
                    print('p: ' + p)
                sleep(0.1)
                total_data = b''
                total_size = 0
                counter = 0
            except:
                total_data += binary_data
            print(counter)
            counter += 1
        else:
            print('DISCOVERY')
            desktop = os.path.normpath(os.path.expanduser('~/Desktop'))

            data, addr = sock.accept()
            print(addr)
            print(data)

            binary_data = data.recv(1024)
            try:
                print('START')
                print('0')
                '''
                if os.path.exists(desktop + r'\hosts.txt'):
                    print('0a')
                    os.remove(desktop + r'\hosts.txt')
                '''
                print('1')
                decoded_data = binary_data.decode('utf-8')
                if 'image_to_process_' in decoded_data:
                    decoded_data = ''
                    continue
                decoded_data = str(decoded_data)
                #decoded_data = decoded_data.split('Reply from ')[1]
                #decoded_data = decoded_data.split(':')[0]
                print(decoded_data)
                print('2')
                print('WHAT ARE YOU: ' + desktop + r'\hosts.txt')
                p = os.path.join(
                    os.path.normpath(os.path.expanduser('~/Desktop')),
                    'hosts.txt')
                print('path: '+ p)
                if 'TTL=' in decoded_data:
                    with open(p, 'w') as binary_file:
                        #print('decoded data: ' + decoded_data)
                        binary_file.write(decoded_data)
                        print('2a')
                        data.close()
                        print('2b')
                sleep(0.1)
                print('3')
                #pyautogui.typewrite(["up"])
                counter = 0
                #is_discovery_complete = True
                print('STOP')
            except:
                print('ERROR')
            print(counter)
            counter += 1
        
    print('complete')
