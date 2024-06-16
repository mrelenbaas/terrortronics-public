# Title: udp_sender file.
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
UDP Sender

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

import random
import socket
import time


PORT = 5005


class UDP:

    def __init__(self):
        self.updater()
    
    def updater(self):
        message = '{},{},{}'.format(
            random.randrange(0, 255),
            random.randrange(0, 255),
            random.randrange(0, 255))
        message = bytes(message, 'utf-8')
        sock = socket.socket(
            socket.AF_INET,
            socket.SOCK_DGRAM,
            socket.IPPROTO_UDP)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        # sock.bind((socket.gethostbyname(socket.gethostname()), 0))
        # sock.sendto(message, ("255.255.255.255", PORT))
        # sock.close()


if __name__ == '__main__':
    udp = UDP()
    while True:
        print(time.time())
        udp.updater()
        time.sleep(1)
