import os
import pathlib
import random
import sched
import sys
import threading
import time

import pygame
import pygame.mixer
import serial

import keyboard
import outputer
import pygame_background
import pygame_cloud
import pygame_tile
import utility_file_io
import utility_pygame


BACKGROUND_R = 248
BACKGROUND_G = 216
BACKGROUND_B = 8
FRAMES_PER_SECOND = 60


HOT_KEYBOARD = {
    # F Row Keys
    # REMEMBER: Esc key is used to teardown application.
    'f1':282,
    'f2':283,
    'f3':284,
    'f4':285,
    'f5':286,
    'f6':287,
    'f7':288,
    'f8':289,
    'f9':290,
    'f10':291,
    'f11':292,
    'f12':293,
    # REMEMBER: Music key is unknown by Pygame.
    # REMEMBER: Screen key is unknown by Pygame.
    # Print Screen Row Keys
    'print_screen':316,
    'scroll_lock':302,
    'pause':19,
    # Mute Row Keys
    # REMEMBER: Mute key is unknown by Pygame.
    # REMEMBER: Sound down key is unknown by Pygame.
    # REMEMBER: Sound up key is unknown by Pygame.
    # REMEMBER: Calculator key is unknown by Pygame.
    # Number Row Keys
    'tilde':96,
    'one_top':49,
    'two_top':50,
    'three_top':51,
    'four_top':52,
    'five_top':53,
    'six_top':54,
    'seven_top':55,
    'eight_top':56,
    'nine_top':57,
    'zero_top':48,
    'minus_top':45,
    'plus_top':61,
    'backspace':8,
    # Insert Row Keys
    'insert':247,
    'home':278,
    'page_up':280,
    # Num Lock Row Keys
    'num_lock':300,
    'divide':267,
    'multiply':268,
    'minus':269,
    # Tab Row Keys
    'tab':9,
    'q':113,
    'w':119,
    'e':101,
    'r':114,
    't':216,
    'y':221,
    'u':117,
    'i':105,
    'o':111,
    'p':112,
    'left_bracket':91,
    'right_bracket':93,
    'backslash':92,
    # Delete Row Keys
    'delete':127,
    'end':279,
    'page_down':281,
    # Seven Row Keys
    'seven':263,
    'eight':264,
    'nine':265,
    'plus':270,
    # Caps Lock Row Keys
    'cap_locks':301,
    'a':97,
    's':115,
    'd':100,
    'f':102,
    'g':104,
    'h':105,
    'j':106,
    'k':107,
    'l':108,
    'semi_colon':59,
    'comma':39,
    'enter':13,
    # Four Row Keys
    'four':260,
    'five':261,
    'six':262,
    # Shift Row Keys
    'shift_left':305,
    'z':122,
    'x':120,
    'c':99,
    'v':118,
    'b':98,
    'n':110,
    'm':109,
    ',':44,
    '.':47,
    'forwardslash':48,
    'shift_right':303,
    # Up Arrow Row Keys
    'arrow_up':273,
    # One Row Keys
    'one':257,
    'two':258,
    'three':259,
    'enter_numpad':272,
    # Ctrl Row Keys
    'ctrl_left':306,
    'windows':311,
    'alt_left':308,
    'space':32,
    'alt_right':307,
    'special':319,
    # REMEMBER: Function key is unknown by Pygame.
    'ctrl_right':305,
    # Left Arrow Row Keys
    'arrow_left':76,
    'arrow_down':74,
    'arrow_right':75,
    # Zero Row Keys
    'zero':256,
    'period':266
}


class Main:

    def __init__(self,
                 ser=None,
                 udp_sender=None,
                 udp_receiver=None,
                 tcp_server=None,
                 tcp_client=None,
                 coap_server=None,
                 coap_client=None):
        self.__ser = ser
        self.__udp_sender = udp_sender
        self.__udp_receiver = udp_receiver
        self.__tcp_server = tcp_server
        self.__tcp_client = tcp_client
        self.__coap_server = coap_server
        self.__coap_client = coap_client
        self.__game = Game()
        self.__background = pygame_background.Background(
            self.__game.get_screen())
        self.__clouds_background = pygame_cloud.Clouds(
            self.__game.get_screen())
        # self.__clouds_foreground = pygame_cloud.Clouds(self.__game)
        self.__tiles = pygame_tile.Tiles(
            self.__game.get_screen(),
            "black",
            "green")
        self.__keyboard = keyboard.Keyboard(self.__tiles)
        self.__keyboard_tuple = (0, 0)
        self.__outputer = outputer.Outputer(self.__game.get_screen())
        self.__messages = '100,100,100,'
        self.__decoded_message = ''
        

    def main(self):
        """The main function."""
        while self.__game.is_running:
            if self.__ser != None:
                if self.__keyboard_tuple[0] > 0:
                    self.__ser.write(bytes('0', 'utf-8'))
                elif self.__keyboard_tuple[0] < 0:
                    self.__ser.write(bytes('1', 'utf-8'))
                elif self.__keyboard_tuple[1] > 0:
                    self.__ser.write(bytes('2', 'utf-8'))
                elif self.__keyboard_tuple[1] < 0:
                    self.__ser.write(bytes('3', 'utf-8'))
            self.__background.update(self.__messages)
            self.__clouds_background.update()
            self.__tiles.update(self.__keyboard_tuple, self.__game.get_hot_keyboard())
            # self.__tiles.update(
            #      (pygame.mouse.get_pos()[0], pygame.mouse.get_pos()[1]))
            self.__keyboard_tuple = self.__keyboard.update()
            self.__game.input()
            self.__outputer.updater()
            # self.__clouds_foreground.update()
            self.__game.update()
            if self.__udp_receiver != None:
                self.__udp_receiver.updater()
            if self.__ser != None:
                serialString = self.__ser.readline()
                self.__decoded_message = serialString.decode("Ascii")
                self.__decoded_message = self.__decoded_message.strip('\r\n')
                if self.__decoded_message == '0':
                    self.__messages = '255,100,100,'
                elif self.__decoded_message == '1':
                    self.__messages = '100,255,100,'
                elif self.__decoded_message == '2':
                    self.__messages = '100,100,255,'
                elif self.__decoded_message == '3':
                    self.__messages = '255,255,100,'
        utility_pygame.teardown()


class Game:
    """PyGame specific calls."""

    def __init__(self):
        pygame.init()
        pygame.font.init()
        self.is_running = True
        self.__screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN)
        self.__clock = pygame.time.Clock()
        self.__hot_keyboard = []
        for i in range(102):
            self.__hot_keyboard.append(0)
        self.__playlist = list()
        if os.name == 'posix' and os.uname().nodename != 'raspberrypi':
            self.__playlist.append("/Users/bradleyelenbaas/Desktop/Miracle Earthquake Brkaburr.mp3")
            self.__playlist.append("/Users/bradleyelenbaas/Desktop/Miracle Lightning Bolt Bolt Bolt.mp3")
            self.__playlist.append("/Users/bradleyelenbaas/Desktop/Miracle Lightning Down.mp3")
            self.__playlist.append("/Users/bradleyelenbaas/Desktop/Miracle Lightning Up.mp3")
            self.__playlist.append("/Users/bradleyelenbaas/Desktop/Miracle Rain Bwa Wa.mp3")
            self.__playlist.append("/Users/bradleyelenbaas/Desktop/Miracle Rain Chick Chick Chick Chick Chick.mp3")
            self.__playlist.append("/Users/bradleyelenbaas/Desktop/Miracle Sun Blu Blu Blu.mp3")
            self.__playlist.append("/Users/bradleyelenbaas/Desktop/Miracle Wind Woo Woo Woo.mp3")
        else:
            self.__playlist.append("/home/terrortronics/Desktop/Miracle Earthquake Brkaburr.mp3")
            self.__playlist.append("/home/terrortronics/Desktop/Miracle Lightning Bolt Bolt Bolt.mp3")
            self.__playlist.append("/home/terrortronics/Desktop/Miracle Lightning Down.mp3")
            self.__playlist.append("/home/terrortronics/Desktop/Miracle Lightning Up.mp3")
            self.__playlist.append("/home/terrortronics/Desktop/Miracle Rain Bwa Wa.mp3")
            self.__playlist.append("/home/terrortronics/Desktop/Miracle Rain Chick Chick Chick Chick Chick.mp3")
            self.__playlist.append("/home/terrortronics/Desktop/Miracle Sun Blu Blu Blu.mp3")
            self.__playlist.append("/home/terrortronics/Desktop/Miracle Wind Woo Woo Woo.mp3")
        pygame.mixer.music.load(self.__playlist[random.randrange(8)])
        pygame.mixer.music.play()

    def blit(self, source: pygame.Surface, destingation: tuple):
        self.__screen.blit(source, destingation)
        
    def get_hot_keyboard(self):
        return self.__hot_keyboard

    def get_screen(self):
        return self.__screen

    def fill(self, color: tuple):
        self.__screen.fill(color)

    def input(self):
        """Close the window with [x] button or ESC"""
        # Remember: Do this event loop here, not like the
        # keyboard.Keyboard class.
        self.__hot_keyboard = []
        for i in range(102):
            self.__hot_keyboard.append(0)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.is_running = False
            if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                self.is_running = False
        pressed = pygame.key.get_pressed()
        if pressed[HOT_KEYBOARD['f1']]:
            self.__hot_keyboard[0] = 1
        elif pressed[HOT_KEYBOARD['f2']]:
            self.__hot_keyboard[1] = 1
        elif pressed[HOT_KEYBOARD['f3']]:
            self.__hot_keyboard[2] = 1
        elif pressed[HOT_KEYBOARD['f4']]:
            self.__hot_keyboard[3] = 1
        elif pressed[HOT_KEYBOARD['f5']]:
            self.__hot_keyboard[4] = 1
        elif pressed[HOT_KEYBOARD['f6']]:
            self.__hot_keyboard[5] = 1
        elif pressed[HOT_KEYBOARD['f7']]:
            self.__hot_keyboard[6] = 1
        elif pressed[HOT_KEYBOARD['f8']]:
            self.__hot_keyboard[7] = 1
        elif pressed[HOT_KEYBOARD['f9']]:
            self.__hot_keyboard[8] = 1
        elif pressed[HOT_KEYBOARD['f10']]:
            self.__hot_keyboard[9] = 1
        elif pressed[HOT_KEYBOARD['f11']]:
            self.__hot_keyboard[10] = 1
        elif pressed[HOT_KEYBOARD['f12']]:
            self.__hot_keyboard[11] = 1
        elif pressed[HOT_KEYBOARD['print_screen']]:
            self.__hot_keyboard[12] = 1
        elif pressed[HOT_KEYBOARD['scroll_lock']]:
            self.__hot_keyboard[13] = 1
        elif pressed[HOT_KEYBOARD['pause']]:
            self.__hot_keyboard[14] = 1
        elif pressed[HOT_KEYBOARD['tilde']]:
            self.__hot_keyboard[15] = 1
        elif pressed[HOT_KEYBOARD['one_top']]:
            self.__hot_keyboard[16] = 1
        elif pressed[HOT_KEYBOARD['two_top']]:
            self.__hot_keyboard[17] = 1
        elif pressed[HOT_KEYBOARD['three_top']]:
            self.__hot_keyboard[18] = 1
        elif pressed[HOT_KEYBOARD['four_top']]:
            self.__hot_keyboard[19] = 1
        elif pressed[HOT_KEYBOARD['five_top']]:
            self.__hot_keyboard[20] = 1
        elif pressed[HOT_KEYBOARD['six_top']]:
            self.__hot_keyboard[21] = 1
        elif pressed[HOT_KEYBOARD['seven_top']]:
            self.__hot_keyboard[22] = 1
        elif pressed[HOT_KEYBOARD['eight_top']]:
            self.__hot_keyboard[23] = 1
        elif pressed[HOT_KEYBOARD['nine_top']]:
            self.__hot_keyboard[24] = 1
        elif pressed[HOT_KEYBOARD['zero_top']]:
            self.__hot_keyboard[25] = 1
        elif pressed[HOT_KEYBOARD['minus_top']]:
            self.__hot_keyboard[26] = 1
        elif pressed[HOT_KEYBOARD['plus_top']]:
            self.__hot_keyboard[27] = 1
        elif pressed[HOT_KEYBOARD['backspace']]:
            self.__hot_keyboard[28] = 1
        elif pressed[HOT_KEYBOARD['insert']]:
            self.__hot_keyboard[29] = 1
        elif pressed[HOT_KEYBOARD['home']]:
            self.__hot_keyboard[30] = 1
        elif pressed[HOT_KEYBOARD['page_up']]:
            self.__hot_keyboard[31] = 1
        elif pressed[HOT_KEYBOARD['num_lock']]:
            self.__hot_keyboard[32] = 1
        elif pressed[HOT_KEYBOARD['divide']]:
            self.__hot_keyboard[33] = 1
        elif pressed[HOT_KEYBOARD['multiply']]:
            self.__hot_keyboard[34] = 1
        elif pressed[HOT_KEYBOARD['minus']]:
            self.__hot_keyboard[35] = 1
        elif pressed[HOT_KEYBOARD['tab']]:
            self.__hot_keyboard[36] = 1
        elif pressed[HOT_KEYBOARD['q']]:
            self.__hot_keyboard[37] = 1
        elif pressed[HOT_KEYBOARD['w']]:
            self.__hot_keyboard[38] = 1
        elif pressed[HOT_KEYBOARD['e']]:
            self.__hot_keyboard[39] = 1
        elif pressed[HOT_KEYBOARD['r']]:
            self.__hot_keyboard[40] = 1
        elif pressed[HOT_KEYBOARD['t']]:
            self.__hot_keyboard[41] = 1
        elif pressed[HOT_KEYBOARD['y']]:
            self.__hot_keyboard[42] = 1
        elif pressed[HOT_KEYBOARD['u']]:
            self.__hot_keyboard[43] = 1
        elif pressed[HOT_KEYBOARD['i']]:
            self.__hot_keyboard[44] = 1
        elif pressed[HOT_KEYBOARD['o']]:
            self.__hot_keyboard[45] = 1
        elif pressed[HOT_KEYBOARD['p']]:
            self.__hot_keyboard[46] = 1
        elif pressed[HOT_KEYBOARD['left_bracket']]:
            self.__hot_keyboard[47] = 1
        elif pressed[HOT_KEYBOARD['right_bracket']]:
            self.__hot_keyboard[48] = 1
        elif pressed[HOT_KEYBOARD['backslash']]:
            self.__hot_keyboard[49] = 1
        elif pressed[HOT_KEYBOARD['delete']]:
            self.__hot_keyboard[50] = 1
        elif pressed[HOT_KEYBOARD['end']]:
            self.__hot_keyboard[51] = 1
        elif pressed[HOT_KEYBOARD['page_down']]:
            self.__hot_keyboard[52] = 1
        elif pressed[HOT_KEYBOARD['seven']]:
            self.__hot_keyboard[53] = 1
        elif pressed[HOT_KEYBOARD['eight']]:
            self.__hot_keyboard[54] = 1
        elif pressed[HOT_KEYBOARD['nine']]:
            self.__hot_keyboard[55] = 1
        elif pressed[HOT_KEYBOARD['plus']]:
            self.__hot_keyboard[56] = 1
        elif pressed[HOT_KEYBOARD['cap_locks']]:
            self.__hot_keyboard[57] = 1
        elif pressed[HOT_KEYBOARD['a']]:
            self.__hot_keyboard[58] = 1
        elif pressed[HOT_KEYBOARD['s']]:
            self.__hot_keyboard[59] = 1
        elif pressed[HOT_KEYBOARD['d']]:
            self.__hot_keyboard[60] = 1
        elif pressed[HOT_KEYBOARD['f']]:
            self.__hot_keyboard[61] = 1
        elif pressed[HOT_KEYBOARD['g']]:
            self.__hot_keyboard[62] = 1
        elif pressed[HOT_KEYBOARD['h']]:
            self.__hot_keyboard[63] = 1
        elif pressed[HOT_KEYBOARD['j']]:
            self.__hot_keyboard[64] = 1
        elif pressed[HOT_KEYBOARD['k']]:
            self.__hot_keyboard[65] = 1
        elif pressed[HOT_KEYBOARD['l']]:
            self.__hot_keyboard[66] = 1
        elif pressed[HOT_KEYBOARD['semi_colon']]:
            self.__hot_keyboard[67] = 1
        elif pressed[HOT_KEYBOARD['comma']]:
            self.__hot_keyboard[68] = 1
        elif pressed[HOT_KEYBOARD['enter']]:
            self.__hot_keyboard[69] = 1
        elif pressed[HOT_KEYBOARD['four']]:
            self.__hot_keyboard[70] = 1
        elif pressed[HOT_KEYBOARD['five']]:
            self.__hot_keyboard[71] = 1
        elif pressed[HOT_KEYBOARD['six']]:
            self.__hot_keyboard[72] = 1
        elif pressed[HOT_KEYBOARD['shift_left']]:
            self.__hot_keyboard[73] = 1
        elif pressed[HOT_KEYBOARD['z']]:
            self.__hot_keyboard[74] = 1
        elif pressed[HOT_KEYBOARD['x']]:
            self.__hot_keyboard[75] = 1
        elif pressed[HOT_KEYBOARD['c']]:
            self.__hot_keyboard[76] = 1
        elif pressed[HOT_KEYBOARD['v']]:
            self.__hot_keyboard[77] = 1
        elif pressed[HOT_KEYBOARD['b']]:
            self.__hot_keyboard[78] = 1
        elif pressed[HOT_KEYBOARD['n']]:
            self.__hot_keyboard[79] = 1
        elif pressed[HOT_KEYBOARD['m']]:
            self.__hot_keyboard[80] = 1
        elif pressed[HOT_KEYBOARD[',']]:
            self.__hot_keyboard[81] = 1
        elif pressed[HOT_KEYBOARD['.']]:
            self.__hot_keyboard[82] = 1
        elif pressed[HOT_KEYBOARD['forwardslash']]:
            self.__hot_keyboard[83] = 1
        elif pressed[HOT_KEYBOARD['shift_right']]:
            self.__hot_keyboard[84] = 1
        elif pressed[HOT_KEYBOARD['arrow_up']]:
            self.__hot_keyboard[85] = 1
        elif pressed[HOT_KEYBOARD['one']]:
            self.__hot_keyboard[86] = 1
        elif pressed[HOT_KEYBOARD['two']]:
            self.__hot_keyboard[87] = 1
        elif pressed[HOT_KEYBOARD['three']]:
            self.__hot_keyboard[88] = 1
        elif pressed[HOT_KEYBOARD['enter_numpad']]:
            self.__hot_keyboard[89] = 1
        elif pressed[HOT_KEYBOARD['ctrl_left']]:
            self.__hot_keyboard[90] = 1
        elif pressed[HOT_KEYBOARD['windows']]:
            self.__hot_keyboard[91] = 1
        elif pressed[HOT_KEYBOARD['alt_left']]:
            self.__hot_keyboard[92] = 1
        elif pressed[HOT_KEYBOARD['space']]:
            self.__hot_keyboard[93] = 1
        elif pressed[HOT_KEYBOARD['alt_right']]:
            self.__hot_keyboard[94] = 1
        elif pressed[HOT_KEYBOARD['special']]:
            self.__hot_keyboard[95] = 1
        elif pressed[HOT_KEYBOARD['ctrl_right']]:
            self.__hot_keyboard[96] = 1
        elif pressed[HOT_KEYBOARD['arrow_left']]:
            self.__hot_keyboard[97] = 1
        elif pressed[HOT_KEYBOARD['arrow_down']]:
            self.__hot_keyboard[98] = 1
        elif pressed[HOT_KEYBOARD['arrow_right']]:
            self.__hot_keyboard[99] = 1
        elif pressed[HOT_KEYBOARD['zero']]:
            self.__hot_keyboard[100] = 1
        elif pressed[HOT_KEYBOARD['period']]:
            self.__hot_keyboard[101] = 1

    def get_height(self) -> int:
        return self.__screen.get_height()

    def get_width(self) -> int:
        return self.__screen.get_width()

    def update(self):
        while pygame.mixer.music.get_busy() == False:
            pygame.mixer.music.load(self.__playlist[random.randrange(8)])
            pygame.mixer.music.play()
        pygame.display.update()
        self.__clock.tick(FRAMES_PER_SECOND)
        '''
        if os.name == 'nt':
            pass
        else:
            if button.is_held:
                led.on()
                time.sleep(1)
                buzzer.on()
                time.sleep(1)
                os.system('sudo shutdown -r now')
            else:
                led.off()
                buzzer.off()
        '''


if __name__ == '__main__':
    main = Main()
    main.main()
