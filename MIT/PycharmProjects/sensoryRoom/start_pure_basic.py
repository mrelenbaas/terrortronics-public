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

import pyautogui
import time

from screeninfo import get_monitors

for monitor in get_monitors():
    print(monitor.width)
    print(monitor.height)
    print(str(monitor))
    if monitor.width_mm == 521 and monitor.height_mm == 293:
        print('Touchscreen Found')
        # Click disclaimer.
        x = monitor.width * 0.58
        y = monitor.height * 0.591
        time.sleep(3)
        pyautogui.click(x, y)
        # Click Run.
        x = monitor.width * 0.13
        y = monitor.height * 0.05
        time.sleep(10)
        pyautogui.click(x, y)
        # Click Close.
        x = monitor.width * 0.99
        y = monitor.height * 0.01
        time.sleep(10)
        pyautogui.click(x, y)
        # Click Fullscreen.
        x = monitor.width * 0.45
        y = monitor.height * 0.505
        time.sleep(10)
        pyautogui.click(x, y)
        # Click Screen Resolution (1st).
        x = monitor.width * 0.52
        y = monitor.height * 0.505
        time.sleep(1)
        pyautogui.click(x, y)
        # Click Screen Resolution (2nd).
        x = monitor.width * 0.52
        y = monitor.height * 0.505
        time.sleep(1)
        pyautogui.click(x, y)
        # Click Fullscreen.
        x = monitor.width * 0.45
        y = monitor.height * 0.595
        time.sleep(1)
        pyautogui.click(x, y)
    else:
        print('Unknown Screen Found')
        # Click disclaimer.
        x = monitor.width * 0.56
        y = monitor.height * 0.57
        time.sleep(3)
        pyautogui.click(x, y)
        # Click Run.
        x = monitor.width * 0.097
        y = monitor.height * 0.04
        time.sleep(10)
        pyautogui.click(x, y)
        # Click Close.
        x = monitor.width * 0.99
        y = monitor.height * 0.01
        time.sleep(10)
        pyautogui.click(x, y)
        # Click Fullscreen.
        x = monitor.width * 0.45
        y = monitor.height * 0.505
        time.sleep(10)
        pyautogui.click(x, y)
        # Click Screen Resolution (1st).
        x = monitor.width * 0.52
        y = monitor.height * 0.505
        time.sleep(1)
        pyautogui.click(x, y)
        # Click Screen Resolution (2nd).
        x = monitor.width * 0.52
        y = monitor.height * 0.505
        time.sleep(1)
        pyautogui.click(x, y)
        # Click Fullscreen.
        x = monitor.width * 0.46
        y = monitor.height * 0.575
        time.sleep(1)
        pyautogui.click(x, y)
print('Complete')
