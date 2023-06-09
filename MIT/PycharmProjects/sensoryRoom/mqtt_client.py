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

"""MQTT client example from https://pypi.org/project/paho-mqtt/
"""


__version__ = '0.1'
__author__ = 'Bradley Elenbaas'


import paho.mqtt.client as mqtt


def on_connect(client, userdata, flags, rc):# Connect callback.
    print("Connected with result code "+str(rc))

    client.subscribe("$SYS/#")

def on_message(client, userdata, msg):# Message callback.
    print(msg.topic+" "+str(msg.payload))


if __name__ == '__main__':
    """Setup client and start main loop."""
    client = mqtt.Client()

    client.on_connect = on_connect
    client.on_message = on_message
    client.connect("mqtt.eclipse.org", 1883, 60)
    client.loop_forever()
