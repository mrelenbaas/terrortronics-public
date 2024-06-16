# Title: sensory_room file.
# Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
# Version: 2
# Date: September 15, 2023
#
# Intellectual Property:
# Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
#
# License:
# This file is owned by Terrortronics / Bradley Elenbaas.
# This file observes the MIT License.

"""
Sensory Room

Description
-----------
Empty.

Circuit
-------
- Empty.

Libraries
---------
- Empty.

Notes
-----
- Empty.

TODO
----
- Empty.

Author(s)
---------
- Bradley Elenbaas (mr.elenbaas@gmail.com)
- Version 2
- Date: September 15, 2023

Intellectual Property
---------------------
Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

License
-------
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

Pins
----
- Empty.

Resources
---------
- Empty.

WARNINGS
--------
- Empty.
"""

import argparse
import os
import pathlib
import random
import sched
import socket
import sys
import threading
import time
import tkinter
import tkinter.messagebox
from timer import Timer

import pygame
import pygame.mixer
import serial

import coap_client
import coap_server
import game
import keyboard
import outputer
import pygame_background
import pygame_cloud
import pygame_tile
import tcp_client
import tcp_server
import udp_receiver
import udp_sender
import utility_file_io
import utility_pygame


ABOUT_CAPTION = 'About SoftfootFalls'
ABOUT_LABEL = 'About'
ABOUT_TEXT = 'SoftfootFalls by Bradley Elenbaas (c)2020'
PRINT = 'FPS: '
QUIT_CAPTION = 'Quit'
QUIT_TEXT = 'Do you really wish to quit?'
ROOT_PROTOCOL = 'WM_DELETE_WINDOW'
STATUS_TEXT = 'FPS'
WINDOW_CAPTION = 'SoftfootFalls'

TEXT_WIDTH = 50
ON_TEXT = '{:<{}}'.format('LED On', TEXT_WIDTH)
OFF_TEXT = '{:<{}}'.format('LED Off', TEXT_WIDTH)
START_TEXT = '{:<{}}'.format('Start', TEXT_WIDTH)
STATUS_TEXT = '{:<{}}'.format('[STATUS LINE]', TEXT_WIDTH)
QUIT_TEXT = '{:<{}}'.format('Quit', TEXT_WIDTH)

GUI_FLAG = '-g'
GUI_NAME = '--gui'
GUI_HELP = 'The application will start with a GUI.'

ser = None
arduino_prefix = '/dev/ttyACM'
ARDUINO_BAUD_RATE = 9600
ARDUINO_TIMEOUT = 0


def callback_about():
    # REMEMBER: Keep an example of a global function.
    tkinter.messagebox.showinfo(ABOUT_CAPTION, ABOUT_TEXT)


def callback_start():
    # Socket.
    udp1 = udp_sender.UDP()
    udp2 = udp_receiver.UDP()
    tcp1 = tcp_server.Main()
    # tcp1.main()
    tcp2 = tcp_client.Main()
    # tcp2.main()
    coap1 = coap_server.Main()
    # coap1.main()
    coap_client.main()
    # Game.
    main = game.Main(ser, udp1, udp2)
    main.main()


def callback_led_on():
    if ser != None:
        ser.write(bytes('0', 'utf-8'))


def callback_led_off():
    if ser != None:
        ser.write(bytes('1', 'utf-8'))


class GUI:
    """
    Manages the tkinter library.

    Attributes
    ----------
    """

    def __init__(self):
        # Tkinter.
        self.__root = tkinter.Tk()
        self.__root.protocol(ROOT_PROTOCOL, self.callback_quit)
        self.__root.title(WINDOW_CAPTION)
        menubar = tkinter.Menu(self.__root)
        menubar.add_command(label=ABOUT_LABEL, command=callback_about)
        tkinter.Button(self.__root,
                       text=START_TEXT,
                       command=callback_start).pack()
        tkinter.Button(self.__root,
                       text=QUIT_TEXT,
                       command=self.__root.destroy).pack()
        tkinter.Button(self.__root,
                       text=ON_TEXT,
                       command=callback_led_on).pack()
        tkinter.Button(self.__root,
                       text=OFF_TEXT,
                       command=callback_led_off).pack()
        self.__root.config(menu=menubar)
        self.__main_dialog = tkinter.Frame(self.__root)
        self.__status_line = tkinter.Label(self.__main_dialog,
                                           relief=tkinter.SUNKEN,
                                           anchor=tkinter.W)
        self.__status_line.config(text=STATUS_TEXT)
        self.__timer = Timer()
        self.__timer.set_callback(self.__root.title)
        self.__status_line.pack(side=tkinter.BOTTOM, fill=tkinter.X)
        self.__main_dialog.pack()
    
    def destroy(self):
        self.__main_dialog.destroy()

    def callback_quit(self):
        if tkinter.messagebox.askokcancel(QUIT_CAPTION, QUIT_TEXT):
            self.__root.destroy()

    def updater(self):
        self.__main_dialog.update()
        self.__timer.updater()


if __name__ == '__main__':
    print('---')
    print(os.uname().nodename)
    # Serial.
    for i in range(256):
        try:
            ser = serial.Serial('{}{}'.format(arduino_prefix,
                                              i),
                                ARDUINO_BAUD_RATE,
                                timeout=ARDUINO_TIMEOUT)
            break
        except serial.SerialException:
            pass
    # Parser.
    parser = argparse.ArgumentParser(sys.argv[0])
    parser.add_argument(
        GUI_FLAG,
        GUI_NAME,
        help=GUI_HELP,
        type=bool,
        default=True)
    args = parser.parse_args()
    if args.gui:
        gui = GUI()
        while True:
            # REMEMBER: This call will still occur even if the flow is
            # blocked during the callback_quit() function.
            try:
                gui.updater()
            except:
                pass
    else:
        callback_start()
