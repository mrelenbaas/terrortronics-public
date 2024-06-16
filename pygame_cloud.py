import os
import random
import time

import pygame

import utility_file_io

CLOUDS_PERIOD_MAX = 120
CLOUDS_PERIOD_MIN = 60
CLOUDS_SPEED_X_MAX = 3
CLOUDS_SPEED_X_MIN = 4
CLOUDS_SPEED_Y_MAX = 0
CLOUDS_SPEED_Y_MIN = 1
CLOUDS_TOTAL = 5

IMAGE_MAX = 8
IMAGE_SIZE = 1024
IMAGE_SIZE_MAX = int(IMAGE_SIZE * 0.60)
IMAGE_SIZE_MIN = int(IMAGE_SIZE * 0.40)


class Cloud:

    def __init__(self, surface, is_warming=True):
        self.__surface = surface
        self.__is_warming = is_warming
        self.__duration = 0.0
        self.__image = None
        self.__progress = 0.0
        self.__period_start = 0.0
        self.__start_x = 0.0
        self.__start_y = 0.0
        self.__stop_x = 0.0
        self.__stop_y = 0.0
        self.__x = 0.0
        self.__y = 0.0
        self.generate()

    def generate(self):
        filename = os.path.join(
            utility_file_io.get_path(),
            utility_file_io.get_filename(utility_file_io.get_path()))
        self.__image = pygame.image.load(filename)
        scale = random.randint(IMAGE_SIZE_MIN, IMAGE_SIZE_MAX)
        self.__image = pygame.transform.smoothscale(
            self.__image,
            (scale, scale))
        self.__duration = random.randint(
            CLOUDS_PERIOD_MIN,
            CLOUDS_PERIOD_MAX)
        self.__start_x = -self.__image.get_width()
        if self.__is_warming:
            self.__start_x += random.randint(
                0,
                self.__surface.get_width())
            self.__is_warming = False
        self.__stop_x = self.__surface.get_width()
        self.__stop_x += self.__image.get_width()
        self.__start_y = random.randint(
            -self.__image.get_height(),
            self.__surface.get_height() + self.__image.get_height())
        self.__stop_y = random.randint(
            -self.__image.get_height(),
            self.__surface.get_height() + self.__image.get_height())
        self.__period_start = time.time()

    def update(self):
        self.__progress = time.time() - self.__period_start
        self.__progress /= self.__duration
        if self.__progress >= 1.0:
            self.generate()
        self.__x = abs(self.__start_x)
        self.__x += abs(self.__stop_x)
        self.__x *= self.__progress
        self.__x += self.__start_x
        self.__x = int(self.__x)
        self.__y = abs(self.__start_y)
        self.__y += abs(self.__stop_y)
        self.__y *= self.__progress
        self.__y += self.__start_y
        self.__y = int(self.__y)
        self.__surface.blit(self.__image, (self.__x, self.__y))


class Clouds:

    def __init__(self, surface):
        self.__surface = surface
        self.__clouds = self.__generate_clouds(CLOUDS_TOTAL)

    def __generate_clouds(self, length: int) -> list:
        self.__clouds = []
        for part in range(length):
            self.__clouds.append(Cloud(self.__surface))
        return self.__clouds

    def update(self):
        # self.__clouds[random.randint(0, len(self.__clouds) - 1)].update()
        for cloud in self.__clouds:
            cloud.update()


if __name__ == '__main__':
    pygame.init()
    screen = pygame.display.set_mode((500, 500))
    clock = pygame.time.Clock()
    clouds = Clouds(screen)
    while True:
        clouds.update()
        pygame.display.update()
        clock.tick(60)
