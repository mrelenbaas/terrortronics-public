"""
Copyright 2023 Bradley Elenbaas

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files
(the “Software”), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
"""

import socket

import pygame
import serial


DELAY = 2
PORT = 5005


class UDP:

    def __init__(self, ser=None):
        pygame.init()
        pygame.display.set_mode((100, 100))
        clock = pygame.time.Clock()
        while True:
            pygame.display.update()
            clock.tick(60)
            message = b'1'
            for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_0:
                        message = b'0'
            if ser is not None and ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').rstrip()
                print(line)
                message = b'{}'.format(line)
            sock = socket.socket(
                socket.AF_INET,
                socket.SOCK_DGRAM,
                socket.IPPROTO_UDP)
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
            sock.bind((socket.gethostbyname(socket.gethostname()), 0))
            sock.sendto(message, ("255.255.255.255", PORT))
            sock.close()


class Main:

    def __init__(self):
        ser = None
        try:
            ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
        except:
            pass
        UDP(ser=ser)


if __name__ == '__main__':
    main = Main()
