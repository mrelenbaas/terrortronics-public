"""
Sensory Room
main.py

Description
-----------
Setup Tkinter, PySerial, UDP, TCP, and CoAP.

Circuit
-------
- Empty.

Libraries
---------
PyGame (LGPL)

https://www.gnu.org/licenses/lgpl-3.0.en.html

https://www.pygame.org/wiki/about

PySerial (BSD)

Copyright (c) 2001-2020 Chris Liechti <cliechti@gmx.net>

All Rights Reserved.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Notes
-----
- Empty.

Author(s)
---------
- Bradley Elenbaas (mr.elenbaas@gmail.com)
- Version 3
- Date: [Month Day], 2024

Intellectual Property
---------------------
Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

License
-------
MIT - sensoryRoom Application

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
import sys
import tkinter
import tkinter.messagebox
from timer import Timer

import serial

import coap_client
import coap_server
import game
import tcp_client
import tcp_server
import udp_receiver
import udp_sender


ABOUT_CAPTION = 'About Sensory Room'
ABOUT_LABEL = 'About'
ABOUT_TEXT = 'Sensory Room by Bradley Elenbaas (c)2020'
PRINT = 'FPS: '
QUIT_CAPTION = 'Quit'
QUIT_TEXT = 'Do you really wish to quit?'
ROOT_PROTOCOL = 'WM_DELETE_WINDOW'
STATUS_TEXT = 'FPS'
WINDOW_CAPTION = 'Sensory Room'

TEXT_WIDTH = 50
ON_TEXT = '{:<{}}'.format('LED On', TEXT_WIDTH)
OFF_TEXT = '{:<{}}'.format('LED Off', TEXT_WIDTH)
START_TEXT = '{:<{}}'.format('Start', TEXT_WIDTH)
STATUS_TEXT_2 = '{:<{}}'.format('[STATUS LINE]', TEXT_WIDTH)
QUIT_TEXT_2 = '{:<{}}'.format('Quit', TEXT_WIDTH)

GUI_FLAG = '-g'
GUI_NAME = '--gui'
GUI_HELP = 'The application will start with a GUI.'

ser = None
arduino_prefix = '/dev/ttyACM'
ARDUINO_BAUD_RATE = 9600
ARDUINO_MAX_PORT = 255
ARDUINO_TIMEOUT = 0


DECODE_FORMAT = 'utf-8'
LED_ON = bytes('0', DECODE_FORMAT)
LED_OFF = bytes('1', DECODE_FORMAT)


def callback_about():
    """
    Called when the 'about' button on the menubar is pressed.
    """
    # REMEMBER: Keep an example of a global function.
    tkinter.messagebox.showinfo(ABOUT_CAPTION, ABOUT_TEXT)


def callback_start():
    """
    Called when the 'start' button is pressed. Setup udp, tcp, coap, and game.
    """
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
    game.Main(ser,
              udp_sender=udp1,
              udp_receiver=udp2,
              tcp_server=tcp1,
              tcp_client=tcp2,
              coap_server=coap1,
              coap_client=None).main()


def callback_led_on():
    """
    Called when the 'on' button is pressed.
    """
    if ser is not None:
        ser.write(LED_ON)


def callback_led_off():
    """
    Called when the 'off' button is pressed.
    """
    if ser is not None:
        ser.write(LED_OFF)


class GUI:
    """
    Manages the tkinter library.
    """

    def __init__(self):
        """
        Setup Tkinter GUI.
        """
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
                       text=QUIT_TEXT_2,
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
        self.__status_line.config(text=STATUS_TEXT_2)
        self.__timer = Timer()
        self.__timer.set_callback(self.__root.title)
        self.__status_line.pack(side=tkinter.BOTTOM, fill=tkinter.X)
        self.__main_dialog.pack()

    def callback_quit(self):
        """
        Quit Tkinter GUI application.
        """
        if tkinter.messagebox.askokcancel(QUIT_CAPTION, QUIT_TEXT):
            self.__root.destroy()

    def updater(self):
        """
        Update Tkinter.
        """
        self.__main_dialog.update()
        self.__timer.updater()


if __name__ == '__main__':
    """
    Setup serial, parse CLI arguments, and GUI.
    """
    # Serial.
    for i in range(ARDUINO_MAX_PORT):
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
            except OSError as err:
                print(err)
    else:
        callback_start()
