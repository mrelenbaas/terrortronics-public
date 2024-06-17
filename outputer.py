# Title: outputer file.
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
import getpass
import os
import time

import pygame

from timer import Timer
import utility

# Global Constants
COLOR_BLUE = (0, 0, 255)
"""Blue."""
print(os.name)
if os.name == 'posix' and os.uname().nodename != 'raspberrypi':
    print('is posix')
else:
    print('is not posix')
if os.name == 'posix' and os.uname().nodename != 'raspberrypi':
    FILENAME_BACKGROUND = os.path.join(os.sep, 'Users', getpass.getuser(),
                                       'Desktop', 'sensoryRoom', 'textures',
                                       'background.jpg')

else:
    FILENAME_BACKGROUND = os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'background.jpg')
"""Background filename."""
ORIGIN_X = 0
"""Origin x."""
ORIGIN_Y = 0
"""Origin y."""
WINDOW_CAPTION = 'SoftfootFalls'
"""Window caption."""
WINDOW_HEIGHT = int(720 / 2)  # 480 #int(2550/4)
"""Window height."""
WINDOW_WIDTH = int(1280 / 2)  # 720 #int(3300/4)
"""Window width."""
WINDOW_SIZE = (WINDOW_WIDTH, WINDOW_HEIGHT)
"""Window width and height."""

PRINT = 'FPS: '
if os.name == 'posix' and os.uname().nodename != 'raspberrypi':
    FILENAME_MONITOR = os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'background2.jpg')
else:
    FILENAME_MONITOR = os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'background2.jpg')
if os.name == 'posix' and os.uname().nodename != 'raspberrypi':
    MONITOR_FILENAMES = [os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_0.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_1.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_2.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_3.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_4.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_5.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_6.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_7.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_8.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_9.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_10.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_11.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_12.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_13.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_14.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_15.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_16.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_17.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_18.jpg'),
                         os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_19.jpg'),]
else:
    MONITOR_FILENAMES = [os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_0.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_1.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_2.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_3.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_4.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_5.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_6.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_7.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_8.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_9.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_10.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_11.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_12.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_13.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_14.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_15.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_16.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_17.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_18.jpg'),
                         os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'monitor_19.jpg'),]
MONITOR_X = -int((512 * 0.20))
MONITOR_Y = -int((512 * 0.30))
if os.name == 'posix' and os.uname().nodename != 'raspberrypi':
    FILENAME_CAT = os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'cat.png')
else:
    FILENAME_CAT = os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'cat.png')
CAT_X = 810
CAT_Y = 70
CAT_X2 = CAT_X + 10
CAT_Y2 = CAT_Y
if os.name == 'posix' and os.uname().nodename != 'raspberrypi':
    NUMBER_FILENAMES = [os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_0.jpg'),
                        os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_1.jpg'),
                        os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_2.jpg'),
                        os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_3.jpg'),
                        os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_4.jpg'),
                        os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_5.jpg'),
                        os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_6.jpg'),
                        os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_7.jpg'),
                        os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_8.jpg'),
                        os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_9.jpg'),]
else:
    NUMBER_FILENAMES = [os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_0.jpg'),
                        os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_1.jpg'),
                        os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_2.jpg'),
                        os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_3.jpg'),
                        os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_4.jpg'),
                        os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_5.jpg'),
                        os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_6.jpg'),
                        os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_7.jpg'),
                        os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_8.jpg'),
                        os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'number_9.jpg'),]
NUMBER_WIDTH = 32
NUMBER_COUNT = int(WINDOW_WIDTH / NUMBER_WIDTH)
NUMBER_COUNT_VERTICAL = int(WINDOW_HEIGHT / NUMBER_WIDTH)
NUMBER_X = CAT_X + 195
NUMBER_Y = CAT_Y + 295
NUMBER_X2 = NUMBER_WIDTH + NUMBER_X
NUMBER_Y2 = NUMBER_Y
NUMBER_X3 = NUMBER_WIDTH + NUMBER_X2
NUMBER_Y3 = NUMBER_Y
NUMBER_X4 = NUMBER_WIDTH + NUMBER_X3
NUMBER_Y4 = NUMBER_Y
if os.name == 'posix' and os.uname().nodename != 'raspberrypi':
    FILENAME_MAGIC = os.path.join(os.sep, 'Users', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'magic.jpg')
else:
    FILENAME_MAGIC = os.path.join(os.sep, 'home', getpass.getuser(), 'Desktop', 'sensoryRoom', 'textures', 'magic.jpg')


class Outputer:
    """Output manager.

    Attributes
    ----------
    __block : bool
        Toggles if TRUE is received at update.
    __background : pygame.Surface
        Image to draw as background.
    __window : pygame.Surface
        Application window.
    """

    def __init__(self, window):
        """Pseudo-constructor."""
        self.__timer = Timer()
        self.__timer.set_callback(self.update_text)
        self.__timer2 = Timer(debug=True)
        self.__timer2.set_callback(self.__timer2.printer)
        # Class variables.
        self.__block = False
        self.__background = pygame.image.load(FILENAME_BACKGROUND)
        self.__monitor = pygame.image.load(FILENAME_MONITOR)
        self.__monitor_block = False
        self.__cat = pygame.image.load(FILENAME_CAT)
        self.__numbers = []
        for i in range(len(NUMBER_FILENAMES)):
            self.__numbers.append(pygame.image.load(NUMBER_FILENAMES[i]))
        self.__monitors = []
        print('---')
        for i in range(len(MONITOR_FILENAMES)):
            self.__monitors.append(pygame.image.load(MONITOR_FILENAMES[i]))
        self.__text = ''
        self.__start_pos = pygame.math.Vector2(0, 0)
        self.__end_pos = pygame.math.Vector2(0, 0)
        self.__is_town_scene = False
        self.__wiggle_min = 0
        self.__wiggle_max = 500
        self.__wiggle_size = self.__wiggle_max
        self.__wiggle_position = self.__wiggle_min
        self.__wiggle_right = True
        self.__scale_size = 8
        self.__scale = 0
        self.__scale_out = True
        self.__scale_step = 1
        self.__background_color = pygame.Color('#b1c2c4')
        self.__magic = pygame.image.load(FILENAME_MAGIC)
        # self.__window = pygame.display.set_mode(WINDOW_SIZE)
        self.__window = window
        self.__animation_period = 2.0
        self.__animation_step = 0.0
        self.__animation_now = time.time()
        self.__animation_previous = self.__animation_now
        self.__animation_current = 0.0
        self.__animation_delta = 0.0
        self.__animation_percent = 0.0
        self.__rotation = 0
        self.__rotation_now = 0.0
        self.__rotation_delta = 0.0
        self.__rotation_previous = 0.0
        self.__rotation_period = 10.0
        self.__rotation_current = 0.0
        # Calls.
        pygame.display.set_caption(WINDOW_CAPTION)
        pygame.mouse.set_cursor(*pygame.cursors.diamond)

    def update_text(self, text):
        self.__text = text

    def __draw_bar(self, text, x_start=0, y_start=0):
        texts = list(text)
        for i in range(len(texts)):
            texts[i] = int(texts[i])
        for i in range(len(texts)):
            self.__window.blit(self.__numbers[texts[i]],
                               ((x_start + (NUMBER_WIDTH * i)), y_start))
        for i in range(len(texts), NUMBER_COUNT):
            self.__window.blit(self.__magic,
                               ((x_start + (NUMBER_WIDTH * i)), y_start))

    def __draw_grid(self):
        vertical_offset = 10
        for j in range(1, NUMBER_COUNT_VERTICAL - 2):
            for i in range(1, (NUMBER_COUNT - 2)):
                x = (i * NUMBER_WIDTH + (i * 2))
                y = vertical_offset + (j * NUMBER_WIDTH) + (j * 2)
                self.__window.blit(self.__magic, (x, y))

    def __draw_monitor(self, pressed, count):
        x = int(MONITOR_X + self.__wiggle_position)
        if pressed:
            if count < 100:
                index = int(count / 10)
                self.__window.blit(
                    pygame.transform.rotate(
                        self.__monitors[index + 10],
                        self.__rotation),
                    (x, MONITOR_Y))
            else:
                self.__window.blit(
                    pygame.transform.rotate(
                        self.__monitors[len(self.__monitors) - 1],
                        self.__rotation),
                    (x, MONITOR_Y))
        else:
            if count < 100:
                index = int(count / 10)
                self.__window.blit(
                    pygame.transform.rotate(
                        self.__monitors[index],
                        self.__rotation),
                    (x, MONITOR_Y))
            else:
                self.__window.blit(
                    pygame.transform.rotate(
                        self.__monitors[len(self.__monitors) - 1],
                        self.__rotation),
                    (x, MONITOR_Y))

    def __update_position(self):
        self.__animation_now = time.time()
        self.__delta = self.__animation_now - self.__animation_previous
        self.__animation_previous = self.__animation_now
        self.__animation_current += self.__delta
        self.__percent = self.__animation_current / self.__animation_period
        if self.__percent >= 1.0:
            self.__animation_current = 0.0
            self.__wiggle_right = not self.__wiggle_right
            return
        position = self.__wiggle_max * self.__percent
        if self.__wiggle_right:
            self.__wiggle_position = position
        else:
            self.__wiggle_position = self.__wiggle_max - position

    def __update_rotation(self):
        self.__rotation_now = time.time()
        self.__rotation_delta = self.__rotation_now - self.__rotation_previous
        self.__rotation_previous = self.__rotation_now
        self.__rotation_current += self.__rotation_delta
        self.__rotation_percent = self.__rotation_current
        self.__rotation_percent /= self.__rotation_period
        if self.__rotation_percent >= 1.0:
            self.__rotation_current = 0.0
        self.__rotation = 360.0 * self.__rotation_percent

    def __draw_background(self):
        """Draw PNG background."""
        self.__window.fill(self.__background_color)

    def updater(self): # , pressed, count):
        """
        """
        self.__timer.updater()
        self.__timer2.updater()
        # self.__update_position()
        # self.__update_rotation()
        # self.__draw_background()
        # self.__draw_monitor(pressed, count)
        self.__draw_bar(self.__text)
        # self.__draw_bar(str(count), y_start=(WINDOW_HEIGHT - NUMBER_WIDTH))
        # if count > 100:
        #     self.__is_town_scene = True
        # else:
        #     self.__is_town_scene = False
        if self.__is_town_scene:
            self.__draw_grid()
        pygame.display.update()


if __name__ == '__main__':
    pygame.init()
    screen = pygame.display.set_mode((200, 200))
    clock = pygame.time.Clock()
    outputer = Outputer(screen)
    while True:
        outputer.updater()
        pygame.display.update()
        clock.tick(60)
    