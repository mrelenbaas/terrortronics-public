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

'''
import socket

MCAST_GRP = '224.1.1.1'
MCAST_PORT = 5007
# regarding socket.IP_MULTICAST_TTL
# ---------------------------------
# for all packets sent, after two hops on the network the packet will not 
# be re-sent/broadcast (see https://www.tldp.org/HOWTO/Multicast-HOWTO-6.html)
MULTICAST_TTL = 2

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, MULTICAST_TTL)

# For Python 3, change next line to 'sock.sendto(b"robot", ...' to avoid the
# "bytes-like object is required" msg (https://stackoverflow.com/a/42612820)
sock.sendto("robot", (MCAST_GRP, MCAST_PORT))
'''

#https://stackoverflow.com/questions/64066634/sending-broadcast-in-python

import socket
from time import sleep

import serial

def main():
    interfaces = socket.getaddrinfo(host=socket.gethostname(), port=None, family=socket.AF_INET)
    allips = [ip[-1][0] for ip in interfaces]

    #msg = b'hello world'
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            msg = b'{}'.format(line)

            for ip in allips:
                print(f'sending on {ip}')
                sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)  # UDP
                sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
                sock.bind((ip,0))
                sock.sendto(msg, ("255.255.255.255", 5005))
                sock.close()

        sleep(2)

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    main()