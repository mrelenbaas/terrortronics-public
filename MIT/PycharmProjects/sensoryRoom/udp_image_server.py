#!/usr/bin/env python

import os
import random
import socket, select
from time import gmtime, strftime, sleep
from random import randint

from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
import urllib.request
import io
import binascii

import pyautogui

#image = "tux.png"
FILENAME = 'image_to_process_'
EXTENSION = '.png'

HOST = '192.168.0.255'
PORT = 5005

#sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#server_address = (HOST, PORT)
#sock.connect(server_address)

counter = 0

if __name__ == '__main__':
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    #sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    #sock.settimeout(0.2)
    sock.bind(('', PORT))
    max_size = 170418
    total_data = b''
    total_size = 0
    socket_size = 9216
    while(True):
        desktop = os.path.normpath(os.path.expanduser('~/Desktop'))

        data, addr = sock.recvfrom(socket_size);
        #print('received message: %s' % data)
        #print(data[:3])
        total_data += data
        total_size += socket_size

        #if total_size >= max_size:
        #print('DATA: ' + str(data))
        if 'END' in str(data):
            #index = str(data)
            #stringData = data.decode('ascii')
            #print(stringData)
            #index = stringData.split('END')[-1]
            '''
            if '14' in str(data):
                index = '14'
            elif '13' in str(data):
                index = '13'
            elif '12' in str(data):
                index = '12'
            elif '11' in str(data):
                index = '11'
            elif '10' in str(data):
                index = '10'
            elif '9' in str(data):
                index = '9'
            elif '8' in str(data):
                index = '8'
            elif '7' in str(data):
                index = '7'
            elif '6' in str(data):
                index = '6'
            elif '5' in str(data):
                index = '5'
            elif '4' in str(data):
                index = '4'
            elif '3' in str(data):
                index = '3'
            elif '2' in str(data):
                index = '2'
            elif '1' in str(data):
                index = '1'
            elif '0' in str(data):
                index = '0'
            '''
            print('HERE')
            #print(str(index))
            #print(desktop + r'\PureBasic\Examples\3D\Data\Textures\VGM CON 12.png')
            randomInt = str(randint(0, 14))
            print('randomInt: ' + randomInt)
            os.remove(desktop + r'\PureBasic\Examples\3D\Data\Textures\VGM CON ' + randomInt + '.png')
            with open(desktop + r'\PureBasic\Examples\3D\Data\Textures\VGM CON ' + randomInt + '.png', 'w+b') as binary_file:
                binary_file.write(total_data)
            sleep(1)
            pyautogui.typewrite(["up"])
            total_data = b''
            total_size = 0
            counter = 0
        
        #sleep(0.1)
        print(counter)
        counter += 1
    print('complete')
