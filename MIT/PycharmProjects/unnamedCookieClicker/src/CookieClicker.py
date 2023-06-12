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

import pygame
import math
# Imports
from time import sleep
# TODO: Remember re isn't picked up because its used as string.
import re
import sensors

import cProfile


"""! @brief Example Python program with Doxygen style comments."""
##
# @mainpage Doxygen Example Project
#
# @section description_main Description
# SOMETHING An example Python program demonstrating how to use Doxygen
# style comments for
# generating source code documentation with Doxygen.
#
# @section notes_main Notes
# - SOMETHING Add special project notes here that you want to
# communicate to the user.test.
# - Source:
# https://www.woolseyworkshop.com/2020/06/25/documenting-python-programs-with-doxygen/
#
# Copyright (c) 2020 Woolsey Workshop.  All rights reserved.
##
# @file doxygen_example.py
#
# @brief Example Python program with Doxygen style comments.
#
# @section description_doxygen_example Description
# Example Python program with Doxygen style comments.
#
# @section libraries_main Libraries/Modules
# - time standard library (https://docs.python.org/3/library/time.html)
#   - Access to sleep function.
# - sensors module (local)
#   - Access to Sensor and TempSensor classes.
#
# @section notes_doxygen_example Notes
# - Comments are Doxygen compatible.
#
# @section todo_doxygen_example TODO
# - None.
#
# @section author_doxygen_example Author(s)
# - Created by John Woolsey on 05/27/2020.
# - Modified by John Woolsey on 06/11/2020.
#
# Copyright (c) 2020 Woolsey Workshop.  All rights reserved.

# Original Source:
# https://www.youtube.com/watch?v=7fqQt2Bwobo&list=PLejN69rU111NiOAX74MS7-nSAIY3uoXYo&index=4&t=318s


cProfile.run('re.compile("")')

# Global Constants
# The mode of operation; 0 = normal, 1 = debug.
DEBUG = 1
# The minimum number to map.
MIN_BASE = 1
# The maximum number to map.
MAX_BASE = 10
# The minimum mapped value.
MIN_MAPPED = 0
# The maximum mapped value.
MAX_MAPPED = 255
# Functions


def init():
    """! Initializes the program."""
    if DEBUG:
        print("Initializing program.")


def map_range(number, in_min, in_max, out_min, out_max):
    """! Maps a number from one range to another.
    @param number   The input number to map.
    @param in_min   The minimum value of an input number.
    @param in_max   The maximum value of an input number.
    @param out_min  The minimum value of an output number.
    @param out_max  The maximum value of an output number.
    @return  The mapped number.
    """
    mapped = \
        (number - in_min) * (out_max - out_min) / (in_max - in_min) + out_min
    if out_min <= out_max:
        return max(min(mapped, out_max), out_min)
    return min(max(mapped, out_max), out_min)


def main():
    """! Main program entry."""
    init()  # program initialization
    # Map numbers
    for i in range(MIN_BASE, MAX_BASE + 1):
        print(
            f"Base: {i:2d}, Mapped: "
            f"{map_range(i, MIN_BASE, MAX_BASE, MIN_MAPPED, MAX_MAPPED):5.1f}"
        )
        sleep(0.25)  # wait 250 milliseconds
    # Sensors
    sensor = sensors.Sensor("MySensor")
    print(sensor)
    temp_in = sensors.TempSensor("Inside")
    print(temp_in)
    temp_out = sensors.TempSensor("Outside", "C")
    print(temp_out)
    temp_out.set_unit("K")
    print(temp_out)


pygame.init()

background_img = pygame.image.load('sprites/background_img.png')

cookie_img = pygame.image.load('sprites/cookie.png')

wooden_bar = pygame.image.load('sprites/wooden_bar.png')
upgrades_wooden_bar = pygame.image.load('sprites/upgrades_wooden_bar.png')
buildings_wooden_bar = pygame.image.load('sprites/buildings_wooden_bar.png')
building_display_background = \
    pygame.image.load('sprites/building_display_background.png')

wooden_background = pygame.image.load('sprites/Road.png')

'''Buildings'''
cursor_img = pygame.image.load('sprites/cursor_img.png')
grandma_img = pygame.image.load('sprites/grandma_img.png')
farm_img = pygame.image.load('sprites/farm_img.png')
mine_img = pygame.image.load('sprites/mine_img.png')
factory_img = pygame.image.load('sprites/factory_img.png')
bank_img = pygame.image.load('sprites/bank_img.png')
temple_img = pygame.image.load('sprites/temple_img.png')
wizard_tower_img = pygame.image.load('sprites/wizard_tower_img.png')

cursor_icon = pygame.image.load('sprites/icons/cursor_icon.png')
grandma_icon = pygame.image.load('sprites/icons/grandma_icon.png')
farm_icon = pygame.image.load('sprites/icons/farm_icon.png')
mine_icon = pygame.image.load('sprites/icons/mine_icon.png')
factory_icon = pygame.image.load('sprites/icons/factory_icon.png')
bank_icon = pygame.image.load('sprites/icons/bank_icon.png')
temple_icon = pygame.image.load('sprites/icons/temple_icon.png')
wizard_tower_icon = pygame.image.load('sprites/icons/wizard_tower_icon.png')

'''Upgrades'''
upgrade_background_frame = \
    pygame.image.load('sprites/upgrades/upgrade_background_frame.png')

cursor_upgrade_img = \
    pygame.image.load('sprites/upgrades/cursor_upgrade_img_1.png')
grandma_upgrade_img = \
    pygame.image.load('sprites/upgrades/grandma_upgrade_img_1.png')
farm_upgrade_img = \
    pygame.image.load('sprites/upgrades/farm_upgrade_img_1.png')
mine_upgrade_img = \
    pygame.image.load('sprites/upgrades/mine_upgrade_img_1.png')
factory_upgrade_img = \
    pygame.image.load('sprites/upgrades/factory_upgrade_img_1.png')
bank_upgrade_img = \
    pygame.image.load('sprites/upgrades/bank_upgrade_img_1.png')
temple_upgrade_img = \
    pygame.image.load('sprites/upgrades/temple_upgrade_img_1.png')
wizard_tower_upgrade_img = \
    pygame.image.load('sprites/upgrades/wizard_tower_upgrade_img_1.png')

mouse_upgrade_img = \
    pygame.image.load('sprites/upgrades/mouse_upgrade_img_1.png')

'''Colors'''
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (155, 155, 155)
LIGHT_GREEN = (0, 255, 0)
DARK_BLUE = (51, 90, 114)


class MainCookie:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.length = 250
        self.height = 250

        self.animation_state = 0
    
    def draw(self):
        if self.animation_state > 0:
            cookie_img_scaled = pygame.transform.scale(
                cookie_img,
                (int(0.9*self.length), int(0.9*self.height)))
            window.blit(
                cookie_img_scaled,
                (cookie_img_scaled.get_rect(
                    center=(int(self.x + self.length/2),
                            int(self.y + self.height/2)))))
            self.animation_state -= 1
        else:
            window.blit(
                cookie_img,
                (cookie_img.get_rect(
                    center=(int(self.x + self.length/2),
                            int(self.y + self.height/2)))))

    def collidepoint(self, position):
        return pygame.Rect(
            self.x,
            self.y,
            self.length,
            self.height).collidepoint(position)


class ScoreDisplay:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.length = 100
        self.height = 100

    def draw(self):
        font = pygame.font.Font('font/Acme-Regular.ttf', 24)

        score = font.render('{} clicks'.format(int(user.score)), True, WHITE)
        cps = font.render('per second: {}'.format(int(user.cps)), True, WHITE)
        window.blit(
            score,
            (score.get_rect(
                center=(int(self.x + self.length/2),
                        int(self.y + self.height/2)))))
        window.blit(
            cps,
            (cps.get_rect(
                center=(int(self.x + self.length/2),
                        int(self.y + self.height/2)+20))))


class Building:
    def __init__(
            self,
            name,
            x,
            y,
            image,
            icon,
            base_cost=0,
            increase_per_purchase=0.0,
            cps=0.0):
        self.name = name
        self.x = x
        self.y = y
        self.length = 300
        self.height = 64
        
        self.image = image
        self.icon = icon
        self.base_cost = base_cost
        self.increase_per_purchase = increase_per_purchase
        self.cps = cps

        self.quantity = 0
        self.created = 0

    def collidepoint(self, point):
        return pygame.Rect(
            self.x,
            self.y,
            self.length,
            self.height).collidepoint(point)

    def get_total_cost(self):
        return self.base_cost * self.increase_per_purchase**self.quantity

    def draw(self, solid=True):
        store_cost_font = pygame.font.Font('font/Acme-Regular.ttf', 17)
        store_quantity_font = pygame.font.Font('font/Acme-Regular.ttf', 36)

        icon = self.image
        cost = store_cost_font.render(
            '{}'.format(
                format_number(int(self.get_total_cost()))),
            True,
            LIGHT_GREEN)
        quantity = store_quantity_font.render(
            '{}'.format(self.quantity),
            True,
            GRAY)

        if solid is False:
            icon.set_alpha(100)
        else:
            icon.set_alpha(255)
        window.blit(icon, (self.x, self.y))
        window.blit(cost, (self.x, self.y + self.height - 30))
        window.blit(quantity, (self.x + self.length - 40, self.y + 10))

    def draw_display_box(self):
        building_font = pygame.font.Font('font/Acme-Regular.ttf', 20)
        building_title = building_font.render(
            '{}'.format(self.name),
            True,
            WHITE)

        description_font = pygame.font.Font('font/Acme-Regular.ttf', 12)
        production = description_font.render(
            'Each {} produces {:.1f} clicks per second'.format(
                self.name,
                self.cps),
            True,
            WHITE)
        quantity = description_font.render(
            'You have {} {}s producing {:.1f} clicks per second'.format(
                self.quantity,
                self.name,
                self.cps * self.quantity),
            True,
            WHITE)
        created = description_font.render(
            '{}s have created {} clicks so far'.format(
                self.name,
                math.floor(self.created)),
            True,
            WHITE)

        x_pos = self.x - 380
        y_pos = pygame.mouse.get_pos()[1] - 72

        window.blit(building_display_background, (x_pos, y_pos))
        window.blit(self.icon, (x_pos + 3, y_pos + 3))
        window.blit(building_title, (x_pos + 43, y_pos + 3))

        '''Description'''
        space_between_lines = 16
        window.blit(production, (x_pos + 18, y_pos + 50))
        window.blit(quantity, (x_pos + 18, y_pos + 50 + space_between_lines*1))
        window.blit(created, (x_pos + 18, y_pos + 50 + space_between_lines*2))

    def add_upgrade(self):
        one = 0
        two = 9
        if self.name == 'Cursor':
            if self.quantity == one:
                list_of_upgrades.append(Upgrade(
                    'Reinforced Index Finger one',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))
                list_of_upgrades.append(Upgrade(
                    'Double Click',
                    cost=1000,
                    upgrader='Mouse'))
            elif self.quantity == two:
                list_of_upgrades.append(Upgrade(
                    'Arthritis Prevention Cream',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))
                list_of_upgrades.append(Upgrade(
                    'Double Click two',
                    cost=2000,
                    upgrader='Mouse'))
        elif self.name == 'Grandma':
            if self.quantity == one:
                list_of_upgrades.append(Upgrade(
                    'Forwards from Grandma',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))
            elif self.quantity == two:
                list_of_upgrades.append(Upgrade(
                    'Steel-plated rolling pins',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))
        elif self.name == 'Farm':
            if self.quantity == one:
                list_of_upgrades.append(Upgrade(
                    'Cheap Hoes',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))
            elif self.quantity == two:
                list_of_upgrades.append(Upgrade(
                    'Fertilizer',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))
        elif self.name == 'Mine':
            if self.quantity == one:
                list_of_upgrades.append(Upgrade(
                    'Sugar gas',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))
            elif self.quantity == two:
                list_of_upgrades.append(Upgrade(
                    'Megadrill',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))
        elif self.name == 'Factory':
            if self.quantity == one:
                list_of_upgrades.append(Upgrade(
                    'Sturdier conveyor belt',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))
            elif self.quantity == two:
                list_of_upgrades.append(Upgrade(
                    'Child labor',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))
        elif self.name == 'Bank':
            if self.quantity == one:
                list_of_upgrades.append(Upgrade(
                    'Credit cards',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))
            elif self.quantity == two:
                list_of_upgrades.append(Upgrade(
                    'Taller tellers',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))
        elif self.name == 'Temple':
            if self.quantity == one:
                list_of_upgrades.append(Upgrade(
                    'Golden idols',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))
            elif self.quantity == two:
                list_of_upgrades.append(Upgrade(
                    'Sacrificies',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))
        elif self.name == 'Wizard Tower':
            if self.quantity == one:
                list_of_upgrades.append(Upgrade(
                    'Pointier Hats',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))
            elif self.quantity == two:
                list_of_upgrades.append(Upgrade(
                    'More Upgrades...',
                    cost=self.get_total_cost() * 10,
                    upgrader=self.name))


class Upgrade:
    def __init__(self, name, cost, upgrader):
        self.name = name
        self.cost = cost

        self.x = 700
        self.y = 16
        self.length = 60
        self.height = 60

        self.upgrade = upgrader

        '''Sets images'''
        if upgrader == 'Mouse':
            self.image = mouse_upgrade_img
        elif upgrader == 'Cursor':
            self.image = cursor_upgrade_img
        elif upgrader == 'Grandma':
            self.image = grandma_upgrade_img
        elif upgrader == 'Farm':
            self.image = farm_upgrade_img
        elif upgrader == 'Mine':
            self.image = mine_upgrade_img
        elif upgrader == 'Factory':
            self.image = factory_upgrade_img
        elif upgrader == 'Bank':
            self.image = bank_upgrade_img
        elif upgrader == 'Temple':
            self.image = temple_upgrade_img
        elif upgrader == 'Wizard Tower':
            self.image = wizard_tower_upgrade_img

    def collidepoint(self, position):
        return pygame.Rect(
            self.x,
            self.y,
            self.length,
            self.height).collidepoint(position)

    def draw(self, solid=True):
        icon = self.image
        frame = upgrade_background_frame
        if solid is False:
            icon.set_alpha(100)
            frame.set_alpha(100)
        else:
            icon.set_alpha(255)
            frame.set_alpha(255)

        window.blit(frame, (self.x, self.y))
        window.blit(
            icon,
            (icon.get_rect(center=(int(self.x + self.length/2),
                                   int(self.y + self.height/2)))))

    def draw_display_box(self):
        upgrade_font = pygame.font.Font('font/Acme-Regular.ttf', 20)
        upgrade_title = upgrade_font.render('{}'.format(self.name), True, WHITE)

        cost_font = pygame.font.Font('font/Acme-Regular.ttf', 14)
        cost = cost_font.render(
            'Cost: {}'.format(format_number(self.cost)),
            True,
            LIGHT_GREEN)
        
        description_font = pygame.font.Font('font/Acme-Regular.ttf', 12)
        description = description_font.render(
            '{}s are twice as effifient'.format(self.upgrade),
            True,
            WHITE)

        x_pos = 700 - 380
        y_pos = pygame.mouse.get_pos()[1] - 72
        if y_pos < 0:
            y_pos = 0

        window.blit(building_display_background, (x_pos, y_pos))
        window.blit(self.image, (x_pos + 3, y_pos + 3))
        window.blit(upgrade_title, (x_pos + 43, y_pos + 3))

        '''Cost'''
        window.blit(cost, (x_pos + 10, y_pos + 50))

        '''Description'''
        space_between_lines = 16
        window.blit(description, (x_pos + 10, y_pos + 50 + space_between_lines))

    def upgrade_building(self):
        if self.upgrade == 'Mouse':
            user.click_multiplier *= 2
        elif self.upgrade == 'Cursor':
            cursor.cps *= 2
        elif self.upgrade == 'Grandma':
            grandma.cps *= 2
        elif self.upgrade == 'Farm':
            farm.cps *= 2
        elif self.upgrade == 'Mine':
            mine.cps *= 2
        elif self.upgrade == 'Factory':
            factory.cps *= 2
        elif self.upgrade == 'Bank':
            bank.cps *= 2
        elif self.upgrade == 'Temple':
            temple.cps *= 2
        elif self.upgrade == 'Wizard Tower':
            wizard_tower.cps *= 2


class Player:
    def __init__(self):
        self.score = 0
        self.click_multiplier = 1
        self.cps = 0

    def update_total_cps(self, list_of_buildings_param):
        self.cps = 0
        for buildings in list_of_buildings_param:
            self.cps += buildings.cps * buildings.quantity


window_length = 1000
window_height = 600
window = pygame.display.set_mode((window_length, window_height))

cookie = MainCookie(100, 100)
score_display = ScoreDisplay(100, 0)
user = Player()


'''Buildings'''
store_y = 212
cursor = Building(
    'Cursor',
    700,
    store_y,
    cursor_img,
    cursor_icon,
    base_cost=15,
    increase_per_purchase=1.15,
    cps=0.1)
grandma = Building(
    'Grandma',
    700,
    store_y + 64*1,
    grandma_img,
    grandma_icon,
    base_cost=100,
    increase_per_purchase=1.15,
    cps=1)
farm = Building(
    'Farm',
    700,
    store_y + 64*2,
    farm_img,
    farm_icon,
    base_cost=1100,
    increase_per_purchase=1.15,
    cps=8)
mine = Building(
    'Mine',
    700,
    store_y + 64*3,
    mine_img,
    mine_icon,
    base_cost=12000,
    increase_per_purchase=1.15,
    cps=47)
factory = Building(
    'Factory',
    700,
    store_y + 64*4,
    factory_img,
    factory_icon,
    base_cost=130000,
    increase_per_purchase=1.15,
    cps=260)
bank = Building(
    'Bank',
    700,
    store_y + 64*5,
    bank_img,
    bank_icon,
    base_cost=1400000,
    increase_per_purchase=1.15,
    cps=1400)
temple = Building(
    'Temple',
    700,
    store_y + 64*6,
    temple_img,
    temple_icon,
    base_cost=20000000,
    increase_per_purchase=1.15,
    cps=7000)
wizard_tower = Building(
    'Wizard Tower',
    700, store_y + 64*7,
    wizard_tower_img,
    wizard_tower_icon,
    base_cost=300000000,
    increase_per_purchase=1.15,
    cps=311000)

list_of_buildings = [
    cursor,
    grandma,
    farm,
    mine,
    factory,
    bank,
    temple,
    wizard_tower]

'''Upgrades'''
upgrade_x = 700
upgrade_y = 16
list_of_upgrades = []


def format_number(n):
    if n >= 1000000000:
        if (n / 1000000000) % 1 == 0:
            n = '{:.0f}'.format(n/1000000000)
        else:
            n = '{:.2f}'.format(n/1000000000)
    elif n >= 1000000:
        if (n / 1000000) % 1 == 0:
            n = '{:.0f}'.format(n/1000000)
        else:
            n = '{:.2f}'.format(n/1000000)
    return n


def draw():
    """Draw Background"""
    window.blit(background_img, (0, 0))
    window.blit(wooden_bar, (684, 0))
    window.blit(wooden_background, (700, 0))
    '''Draw Cookie and Score Display'''
    cookie.draw()
    score_display.draw()
    '''Draw buildings'''
    for buildings in list_of_buildings:
        if user.score >= buildings.get_total_cost():
            buildings.draw(solid=True)
        else:
            buildings.draw(solid=False)
        '''Add cookies made through building'''
        user.score += buildings.quantity * buildings.cps * .01
        buildings.created += buildings.quantity * buildings.cps * .01
        '''Draws display box for buildings'''
        if buildings.collidepoint(pygame.mouse.get_pos()):
            buildings.draw_display_box()
    '''Draw upgrades'''
    for i in range(0, len(list_of_upgrades)):
        upgrades = list_of_upgrades[i]
        '''Sets position of upgrade'''
        upgrades.x = upgrade_x + (i % 5) * 60
        upgrades.y = upgrade_y + (i // 5) * 60
        '''Draws solid/transparent'''
        if user.score >= upgrades.cost:
            upgrades.draw(solid=True)
        else:
            upgrades.draw(solid=False)
        if upgrades.collidepoint(pygame.mouse.get_pos()):
            upgrades.draw_display_box()
    '''Draw wooden bars'''
    window.blit(buildings_wooden_bar, (700, store_y - 16))
    window.blit(upgrades_wooden_bar, (700, 0))
    pygame.display.update()


is_running = True
while is_running is True:
    pygame.time.delay(10)
    for event in pygame.event.get():
        if event.type == pygame.MOUSEBUTTONDOWN:
            mouse_pos = event.pos
            '''Click Cookie'''
            if cookie.collidepoint(mouse_pos):
                user.score += 1000 * user.click_multiplier
                cookie.animation_state = 1
            '''Buy Building'''
            for building in list_of_buildings:
                if building.collidepoint(mouse_pos) \
                        and user.score >= building.get_total_cost():
                    '''Unlock Upgrades'''
                    building.add_upgrade()
                    
                    user.score -= building.get_total_cost()
                    building.quantity += 1
                    user.update_total_cps(list_of_buildings)
            for upgrade in list_of_upgrades:
                if upgrade.collidepoint(mouse_pos) \
                        and user.score >= upgrade.cost:
                    user.score -= upgrade.cost
                    upgrade.upgrade_building()
                    list_of_upgrades.remove(upgrade)
                    user.update_total_cps(list_of_buildings)
        if event.type == pygame.QUIT:
            is_running = False
    if 700 < pygame.mouse.get_pos()[0] < 1000:
        if store_y < pygame.mouse.get_pos()[1] < store_y + 50:
            '''Scroll up store menu'''
            if list_of_buildings[0].y < store_y:
                for building in list_of_buildings:
                    building.y += 4
                    '''Make building appear from view if hidden'''
                    if store_y - 4 - 400 <= building.y <= store_y - 400:
                        building.y += 400
            '''Scroll down store menu'''
        elif 550 < pygame.mouse.get_pos()[1] < 600:
            for building in list_of_buildings:
                building.y -= 4
                '''Make building disappear from view once scrolled past'''
                if store_y - 4 <= building.y < store_y:
                    building.y -= 400
    draw()

print('Complete.')
