import time

import pygame

import pygame_tile


class Keyboard:
    
    def __init__(self, Tiles=None):
        self.__tiles = Tiles
        self.__is_up_blocked = False
        self.__is_down_blocked = False
        self.__is_left_blocked = False
        self.__is_right_blocked = False
    
    def update(self):
        i = 0
        j = 0
        pressed = pygame.key.get_pressed()
        if pressed[pygame.K_a] or pressed[pygame.K_LEFT]:
            if self.__is_left_blocked == False:
                if self.__tiles != None:
                    if self.__tiles.get_is_cursor_on_left():
                        i = 1
                    else:
                        i = -1
                self.__is_left_blocked = True
        elif pressed[pygame.K_a] == 0 and pressed[pygame.K_LEFT] == 0:
            self.__is_left_blocked = False
        if pressed[pygame.K_d] or pressed[pygame.K_RIGHT]:
            if self.__is_right_blocked == False:
                if self.__tiles != None:
                    if self.__tiles.get_is_cursor_on_left():
                        i = -1
                    else:
                        i = 1
                self.__is_right_blocked = True
        elif pressed[pygame.K_d] == 0 and pressed[pygame.K_RIGHT] == 0:
            self.__is_right_blocked = False
        if pressed[pygame.K_s] or pressed[pygame.K_DOWN]:
            if self.__is_down_blocked == False:
                j = 12
                self.__is_down_blocked = True
        elif pressed[pygame.K_s] == 0 or pressed[pygame.K_DOWN] == 0:
            self.__is_down_blocked = False
        if pressed[pygame.K_w] or pressed[pygame.K_UP]:
            if self.__is_up_blocked == False:
                j = -12
                self.__is_up_blocked = True
        elif pressed[pygame.K_w] == 0 or pressed[pygame.K_UP] == 0:
            self.__is_up_blocked = False
        return (i, j)


if __name__ == '__main__':
    pygame.init()
    keyboard = Keyboard()
    while True:
        print(str(keyboard.update()) + ', ' + str(time.time()))
