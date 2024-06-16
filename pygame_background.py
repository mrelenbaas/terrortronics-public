import os

import pygame

FILENAME = 'udp_received.txt'


class Background:

    def __init__(self, surface):
        self.__surface = surface

    def update(self, messages):
        try:
            filename = os.path.expanduser('~/Desktop')
            filename = os.path.join(filename, FILENAME)
            with open(filename) as file:
                messages = file.readline()
            messages = messages.split(',')
            self.__surface.fill((
                int(messages[0]),
                int(messages[1]),
                int(messages[2])))
        except OSError:
            messages = messages.split(',')
            self.__surface.fill((
                int(messages[0]),
                int(messages[1]),
                int(messages[2])))


if __name__ == '__main__':
    pygame.init()
    screen = pygame.display.set_mode((200, 200))
    clock = pygame.time.Clock()
    background = Background(screen)
    while True:
        background.update()
        pygame.display.update()
        clock.tick(60)
