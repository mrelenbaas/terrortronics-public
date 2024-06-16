import pygame

COLOR_BORDER = (255, 255, 255)


class Polygon:

    def __init__(self, surface, x1, y1, x2, y2):
        self.__surface = surface
        self.__x1 = x1
        self.__y1 = y1
        self.__x2 = x2
        self.__y2 = y2

    def update(self):
        pygame.draw.line(
            self.__surface,
            COLOR_BORDER,
            (self.__x1, self.__y1),
            (self.__x2, self.__y2))


class Rectangle:

    def __init__(self, surface, x, y, width, height, color):
        self.__surface = surface
        self.__x = x
        self.__y = y
        self.__width = width
        self.__height = height
        self.__color = color

    def update(self):
        pygame.draw.rect(
            self.__surface,
            self.__color,
            pygame.Rect(
                self.__x,
                self.__y,
                self.__width,
                self.__height))


class Tile:

    def __init__(
            self,
            surface,
            vertices,
            background_color,
            foreground_color):
        self.__surface = surface
        self.__vertices = vertices
        self.__background_color = background_color
        self.__foreground_color = foreground_color

    def update(self):
        pygame.draw.polygon(
            self.__surface,
            self.__background_color,
            self.__vertices)
        pygame.draw.lines(
            self.__surface,
            self.__foreground_color,
            True,
            self.__vertices,
            5
        )


class Tiles:

    def __init__(self, surface, background_color, foreground_color):
        self.__surface = surface
        self.__refresh_lists()
        # self.__update_geometry(
        #     self.__surface.get_width() / 2,
        #     self.__surface.get_height() / 2)
        self.__cursor_i = 3
        self.__cursor_j = 84
        self.__odd = False
        self.__is_cursor_on_left = False
        self.__font = pygame.font.SysFont('Comic Sans MS', 20)
        self.__font2 = pygame.font.SysFont('Comic Sans MS', 15)
        self.__cursor_x = 0
        self.__cursor_y = 0
        self.__text = ''
        self.__key_rectangles = []
        self.__minimum_visible = 21
    
    def get_is_cursor_on_left(self):
        return self.__is_cursor_on_left

    def __refresh_lists(self):
        self.__polygons = []
        self.__rectangles = []
        self.__cursor = None
        self.__texts = []

    def __update_geometry(self, camera_x, camera_y, hot_keyboard):
        self.__refresh_lists()
        column_count = 10
        row_count = 10
        color_count = column_count * row_count
        r = 0
        g = 0
        b = 0
        colors = []
        i = 0
        j = 0
        step = (256 * 3) / color_count
        keyboard_i = 0
        while True:
            if i < 256:
                r = i
                g = 0
                b = 0
            elif i < (256 * 2):
                r = 0
                g = i - 256
                b = 0
            elif i < (256 * 3):
                r = 0
                g = 0
                b = i - (256 * 2)
            colors.append((r, g, b))
            i = i + step
            j = j + 1
            if i > (256 * 3):
                break
        x_list = []
        y_list = []
        width = self.__surface.get_width()
        height = self.__surface.get_height()
        for i in range(column_count + 2):
            x_list.append(i * (width / column_count))
        for j in range(row_count + 12):
            y_list.append(height)
        vertex1 = []
        originalVertexX = []
        originalVertexY = []
        vertexX = []
        vertexY = []
        self.__key_rectangles = []
        for i in range(column_count + 2):
            for j in range(row_count + 2):
                originalVertexX.append((width / 2) * (j / column_count))
                originalVertexY.append(0.0)
                vertex1.append((
                    originalVertexX[-1],
                    originalVertexY[-1]
                ))
        midpoints = []
        midpoints2 = []
        for i in range(column_count + 1):
            for j in range(row_count + 1):
                vertexX.append((vertex1[i][0]) * (j / column_count))
                vertexY.append((vertex1[j][1] + camera_y) * (i / row_count))
                midpoints.append((
                    vertexX[-1],
                    vertexY[-1]
                ))
        self.__text = str(self.__cursor_i) + ', ' + str(self.__cursor_j)
        for i in range(len(midpoints)):
            if i > self.__minimum_visible and i < 110:
                self.__rectangles.append(Rectangle(
                    self.__surface,
                    camera_x + midpoints[i][0],
                    camera_y + midpoints[i][1],
                    50,
                    25,
                    COLOR_BORDER
                ))
                self.__rectangles.append(Rectangle(
                    self.__surface,
                    camera_x + midpoints[i][0] + 1,
                    camera_y + midpoints[i][1] + 1,
                    # y + 1 - 25,
                    50 - 2,
                    25 - 2,
                    (200, 0, 200)
                    # "yellow"
                ))
                self.__rectangles.append(Rectangle(
                    self.__surface,
                    camera_x + midpoints[i][0] - 10,
                    camera_y + midpoints[i][1] - 10,
                    # y + 1 - 25,
                    20,
                    20,
                    COLOR_BORDER
                ))
                self.__rectangles.append(Rectangle(
                    self.__surface,
                    camera_x + midpoints[i][0] + 1 - 10,
                    camera_y + midpoints[i][1] + 1 - 10,
                    # y + 1 - 25,
                    20 - 2,
                    20 - 2,
                    (100, 0, 200)
                    # "cyan"
                ))
                # if i > 43 and keyboard_i < 95:
                #     self.__texts.append((
                #         chr(41 + i),
                #         (  
                #             camera_x + midpoints[i][0] - 10 + 4,
                #             camera_y + midpoints[i][1] - 10 + 5)
                #         ))
                #     keyboard_i = keyboard_i + 1
        '''
        for i in range(len(midpoints)):
            # if i % 12 == 0:
            #     continue
            # midpoints
            self.__rectangles.append(Rectangle(
                self.__surface,
                camera_x - midpoints[i][0],
                camera_y + midpoints[i][1],
                # y + 1 - 25,
                50,
                25,
                COLOR_BORDER
            ))
            self.__rectangles.append(Rectangle(
                self.__surface,
                camera_x - midpoints[i][0] + 1,
                camera_y + midpoints[i][1] + 1,
                # y + 1 - 25,
                50 - 2,
                25 - 2,
                (100, 0, 200)
                # "cyan"
            ))
            self.__rectangles.append(Rectangle(
                self.__surface,
                camera_x - midpoints[i][0] - 10 - 1,
                camera_y + midpoints[i][1] - 10 - 1,
                # y + 1 - 25,
                20,
                20,
                COLOR_BORDER
            ))
            self.__rectangles.append(Rectangle(
                self.__surface,
                camera_x - midpoints[i][0]- 10,
                camera_y + midpoints[i][1]- 10,
                # y + 1 - 25,
                20 - 2,
                20 - 2,
                (200, 0, 200)
                # "yellow"
            ))
        '''
        for i in range(len(midpoints)):
            if i > self.__minimum_visible and keyboard_i < 124:
                # self.__texts.append((
                #     chr(41 + i - 24),
                #     (  
                #         (camera_x - midpoints[9][0]) + midpoints[i][0] - 10 + 6,
                #         camera_y + midpoints[i][1] - 10 + 6)
                #     ))
                keyboard_i = keyboard_i + 1
                text_x = (camera_x - midpoints[9][0]) + midpoints[i][0] - 10 + 6
                text_y = camera_y + midpoints[i][1] - 10 + 6
                if (i == 22): # and hot_keyboard[0] == 1):
                    self.__texts.append(('f1', (text_x, text_y)))
                elif (i == 23): # and hot_keyboard[1] == 1):
                    self.__texts.append(('f2', (text_x, text_y)))
                elif (i == 24): # and hot_keyboard[2] == 1):
                    self.__texts.append(('f3', (text_x, text_y)))
                elif (i == 25): # and hot_keyboard[3] == 1):
                    self.__texts.append(('f4', (text_x, text_y)))
                elif (i == 26): # and hot_keyboard[4] == 1):
                    self.__texts.append(('f5', (text_x, text_y)))
                elif (i == 27): # and hot_keyboard[5] == 1):
                    self.__texts.append(('f6', (text_x, text_y)))
                elif (i == 28): # and hot_keyboard[6] == 1):
                    self.__texts.append(('f7', (text_x, text_y)))
                elif (i == 29): # and hot_keyboard[7] == 1):
                    self.__texts.append(('f8', (text_x, text_y)))
                elif (i == 30): # and hot_keyboard[8] == 1):
                    self.__texts.append(('f9', (text_x, text_y)))
                elif (i == 31): # and hot_keyboard[9] == 1):
                    self.__texts.append(('f10', (text_x, text_y)))
                elif (i == 32): # and hot_keyboard[10] == 1):
                    self.__texts.append(('f11', (text_x, text_y)))
                elif (i == 33): # and hot_keyboard[11] == 1):
                    self.__texts.append(('f12', (text_x, text_y)))
                elif (i == 34): # and hot_keyboard[12] == 1):
                    self.__texts.append(('print_screen', (text_x, text_y)))
                elif (i == 35): # and hot_keyboard[13] == 1):
                    self.__texts.append(('scroll_lock', (text_x, text_y)))
                elif (i == 36): # and hot_keyboard[14] == 1):
                    self.__texts.append(('pause', (text_x, text_y)))
                elif (i == 37): # and hot_keyboard[15] == 1):
                    self.__texts.append(('~', (text_x, text_y)))
                elif (i == 38): # and hot_keyboard[16] == 1):
                    self.__texts.append(('1', (text_x, text_y)))
                elif (i == 39): # and hot_keyboard[17] == 1):
                    self.__texts.append(('2', (text_x, text_y)))
                elif (i == 40): # and hot_keyboard[18] == 1):
                    self.__texts.append(('3', (text_x, text_y)))
                elif (i == 41): # and hot_keyboard[19] == 1):
                    self.__texts.append(('4', (text_x, text_y)))
                elif (i == 42): # and hot_keyboard[20] == 1):
                    self.__texts.append(('5', (text_x, text_y)))
                elif (i == 43): # and hot_keyboard[21] == 1):
                    self.__texts.append(('6', (text_x, text_y)))
                elif (i == 44): # and hot_keyboard[22] == 1):
                    self.__texts.append(('7', (text_x, text_y)))
                elif (i == 45): # and hot_keyboard[23] == 1):
                    self.__texts.append(('8', (text_x, text_y)))
                elif (i == 46): # and hot_keyboard[24] == 1):
                    self.__texts.append(('9', (text_x, text_y)))
                elif (i == 47): # and hot_keyboard[25] == 1):
                    self.__texts.append(('0', (text_x, text_y)))
                elif (i == 48): # and hot_keyboard[26] == 1):
                    self.__texts.append(('-', (text_x, text_y)))
                elif (i == 49): # and hot_keyboard[27] == 1):
                    self.__texts.append(('+', (text_x, text_y)))
                elif (i == 50): # and hot_keyboard[28] == 1):
                    self.__texts.append(('backspace', (text_x, text_y)))
                elif (i == 51): # and hot_keyboard[29] == 1):
                    self.__texts.append(('insert', (text_x, text_y)))
                elif (i == 52): # and hot_keyboard[30] == 1):
                    self.__texts.append(('home', (text_x, text_y)))
                elif (i == 53): # and hot_keyboard[31] == 1):
                    self.__texts.append(('page_up', (text_x, text_y)))
                elif (i == 54): # and hot_keyboard[32] == 1):
                    self.__texts.append(('num_lock', (text_x, text_y)))
                elif (i == 55): # and hot_keyboard[33] == 1):
                    self.__texts.append(('/', (text_x, text_y)))
                elif (i == 56): # and hot_keyboard[34] == 1):
                    self.__texts.append(('*', (text_x, text_y)))
                elif (i == 57): # and hot_keyboard[35] == 1):
                    self.__texts.append(('-', (text_x, text_y)))
                elif (i == 58): # and hot_keyboard[36] == 1):
                    self.__texts.append(('tab', (text_x, text_y)))
                elif (i == 59): # and hot_keyboard[37] == 1):
                    self.__texts.append(('q', (text_x, text_y)))
                elif (i == 60): # and hot_keyboard[38] == 1):
                    self.__texts.append(('', (text_x, text_y)))
                elif (i == 61): # and hot_keyboard[39] == 1):
                    self.__texts.append(('e', (text_x, text_y)))
                elif (i == 62): # and hot_keyboard[40] == 1):
                    self.__texts.append(('r', (text_x, text_y)))
                elif (i == 63): # and hot_keyboard[41] == 1):
                    self.__texts.append(('t', (text_x, text_y)))
                elif (i == 64): # and hot_keyboard[42] == 1):
                    self.__texts.append(('y', (text_x, text_y)))
                elif (i == 65): # and hot_keyboard[43] == 1):
                    self.__texts.append(('u', (text_x, text_y)))
                elif (i == 66): # and hot_keyboard[44] == 1):
                    self.__texts.append(('i', (text_x, text_y)))
                elif (i == 67): # and hot_keyboard[45] == 1):
                    self.__texts.append(('o', (text_x, text_y)))
                elif (i == 68): # and hot_keyboard[46] == 1):
                    self.__texts.append(('p', (text_x, text_y)))
                elif (i == 69): # and hot_keyboard[47] == 1):
                    self.__texts.append(('[', (text_x, text_y)))
                elif (i == 70): # and hot_keyboard[48] == 1):
                    self.__texts.append((']', (text_x, text_y)))
                elif (i == 71): # and hot_keyboard[49] == 1):
                    self.__texts.append(('\\', (text_x, text_y)))
                elif (i == 72): # and hot_keyboard[50] == 1):
                    self.__texts.append(('delete', (text_x, text_y)))
                elif (i == 73): # and hot_keyboard[51] == 1):
                    self.__texts.append(('end', (text_x, text_y)))
                elif (i == 74): # and hot_keyboard[52] == 1):
                    self.__texts.append(('page_down', (text_x, text_y)))
                elif (i == 75): # and hot_keyboard[53] == 1):
                    self.__texts.append(('7', (text_x, text_y)))
                elif (i == 76): # and hot_keyboard[54] == 1):
                    self.__texts.append(('8', (text_x, text_y)))
                elif (i == 77): # and hot_keyboard[55] == 1):
                    self.__texts.append(('9', (text_x, text_y)))
                elif (i == 78): # and hot_keyboard[56] == 1):
                    self.__texts.append(('+', (text_x, text_y)))
                elif (i == 79): # and hot_keyboard[57] == 1):
                    self.__texts.append(('cap_locks', (text_x, text_y)))
                elif (i == 80): # and hot_keyboard[58] == 1):
                    self.__texts.append(('a', (text_x, text_y)))
                elif (i == 81): # and hot_keyboard[59] == 1):
                    self.__texts.append(('s', (text_x, text_y)))
                elif (i == 82): # and hot_keyboard[60] == 1):
                    self.__texts.append(('d', (text_x, text_y)))
                elif (i == 83): # and hot_keyboard[61] == 1):
                    self.__texts.append(('f', (text_x, text_y)))
                elif (i == 84): # and hot_keyboard[62] == 1):
                    self.__texts.append(('g', (text_x, text_y)))
                elif (i == 85): # and hot_keyboard[63] == 1):
                    self.__texts.append(('h', (text_x, text_y)))
                elif (i == 86): # and hot_keyboard[64] == 1):
                    self.__texts.append(('j', (text_x, text_y)))
                elif (i == 87): # and hot_keyboard[65] == 1):
                    self.__texts.append(('k', (text_x, text_y)))
                elif (i == 88): # and hot_keyboard[66] == 1):
                    self.__texts.append(('l', (text_x, text_y)))
                elif (i == 89): # and hot_keyboard[67] == 1):
                    self.__texts.append((';', (text_x, text_y)))
                elif (i == 90): # and hot_keyboard[68] == 1):
                    self.__texts.append((',', (text_x, text_y)))
                elif (i == 91): # and hot_keyboard[69] == 1):
                    self.__texts.append(('enter', (text_x, text_y)))
                elif (i == 92): # and hot_keyboard[70] == 1):
                    self.__texts.append(('4', (text_x, text_y)))
                elif (i == 93): # and hot_keyboard[71] == 1):
                    self.__texts.append(('5', (text_x, text_y)))
                elif (i == 94): # and hot_keyboard[72] == 1):
                    self.__texts.append(('6', (text_x, text_y)))
                elif (i == 95): # and hot_keyboard[73] == 1):
                    self.__texts.append(('shift_left', (text_x, text_y)))
                elif (i == 96): # and hot_keyboard[74] == 1):
                    self.__texts.append(('z', (text_x, text_y)))
                elif (i == 97): # and hot_keyboard[75] == 1):
                    self.__texts.append(('x', (text_x, text_y)))
                elif (i == 98): # and hot_keyboard[76] == 1):
                    self.__texts.append(('c', (text_x, text_y)))
                elif (i == 99): # and hot_keyboard[77] == 1):
                    self.__texts.append(('v', (text_x, text_y)))
                elif (i == 100): # and hot_keyboard[78] == 1):
                    self.__texts.append(('b', (text_x, text_y)))
                elif (i == 101): # and hot_keyboard[79] == 1):
                    self.__texts.append(('n', (text_x, text_y)))
                elif (i == 102): # and hot_keyboard[80] == 1):
                    self.__texts.append(('m', (text_x, text_y)))
                elif (i == 103): # and hot_keyboard[81] == 1):
                    self.__texts.append((',', (text_x, text_y)))
                elif (i == 104): # and hot_keyboard[82] == 1):
                    self.__texts.append(('.', (text_x, text_y)))
                elif (i == 105): # and hot_keyboard[83] == 1):
                    self.__texts.append(('/', (text_x, text_y)))
                elif (i == 106): # and hot_keyboard[84] == 1):
                    self.__texts.append(('shift_right', (text_x, text_y)))
                elif (i == 107): # and hot_keyboard[85] == 1):
                    self.__texts.append(('arrow_up', (text_x, text_y)))
                elif (i == 108): # and hot_keyboard[86] == 1):
                    self.__texts.append(('1', (text_x, text_y)))
                elif (i == 109): # and hot_keyboard[87] == 1):
                    self.__texts.append(('2', (text_x, text_y)))
                elif (i == 110): # and hot_keyboard[88] == 1):
                    self.__texts.append(('3', (text_x, text_y)))
                elif (i == 111): # and hot_keyboard[89] == 1):
                    self.__texts.append(('enter_numpad', (text_x, text_y)))
                elif (i == 112): # and hot_keyboard[90] == 1):
                    self.__texts.append(('ctrl_left', (text_x, text_y)))
                elif (i == 113): # and hot_keyboard[91] == 1):
                    self.__texts.append(('windows', (text_x, text_y)))
                elif (i == 114): # and hot_keyboard[92] == 1):
                    self.__texts.append(('alt_left', (text_x, text_y)))
                elif (i == 115): # and hot_keyboard[93] == 1):
                    self.__texts.append(('space', (text_x, text_y)))
                elif (i == 116): # and hot_keyboard[94] == 1):
                    self.__texts.append(('alt_right', (text_x, text_y)))
                elif (i == 117): # and hot_keyboard[95] == 1):
                    self.__texts.append(('special', (text_x, text_y)))
                elif (i == 118): # and hot_keyboard[96] == 1):
                    self.__texts.append(('ctrl_right', (text_x, text_y)))
                elif (i == 119): # and hot_keyboard[97] == 1):
                    self.__texts.append(('arrow_left', (text_x, text_y)))
                elif (i == 120): # and hot_keyboard[98] == 1):
                    self.__texts.append(('arrow_down', (text_x, text_y)))
                elif (i == 121): # and hot_keyboard[99] == 1):
                    self.__texts.append(('arrow_right', (text_x, text_y)))
                elif (i == 122): # and hot_keyboard[100] == 1):
                    self.__texts.append(('0', (text_x, text_y)))
                elif (i == 123): # and hot_keyboard[101] == 1):
                    self.__texts.append(('.', (text_x, text_y)))
                if (i == 22 and hot_keyboard[0] == 1) \
                or (i == 23 and hot_keyboard[1] == 1) \
                or (i == 24 and hot_keyboard[2] == 1) \
                or (i == 25 and hot_keyboard[3] == 1) \
                or (i == 26 and hot_keyboard[4] == 1) \
                or (i == 27 and hot_keyboard[5] == 1) \
                or (i == 28 and hot_keyboard[6] == 1) \
                or (i == 29 and hot_keyboard[7] == 1) \
                or (i == 30 and hot_keyboard[8] == 1) \
                or (i == 31 and hot_keyboard[9] == 1) \
                or (i == 32 and hot_keyboard[10] == 1) \
                or (i == 33 and hot_keyboard[11] == 1) \
                or (i == 34 and hot_keyboard[12] == 1) \
                or (i == 35 and hot_keyboard[13] == 1) \
                or (i == 36 and hot_keyboard[14] == 1) \
                or (i == 37 and hot_keyboard[15] == 1) \
                or (i == 38 and hot_keyboard[16] == 1) \
                or (i == 39 and hot_keyboard[17] == 1) \
                or (i == 40 and hot_keyboard[18] == 1) \
                or (i == 41 and hot_keyboard[19] == 1) \
                or (i == 42 and hot_keyboard[20] == 1) \
                or (i == 43 and hot_keyboard[21] == 1) \
                or (i == 44 and hot_keyboard[22] == 1) \
                or (i == 45 and hot_keyboard[23] == 1) \
                or (i == 46 and hot_keyboard[24] == 1) \
                or (i == 47 and hot_keyboard[25] == 1) \
                or (i == 48 and hot_keyboard[26] == 1) \
                or (i == 49 and hot_keyboard[27] == 1) \
                or (i == 50 and hot_keyboard[28] == 1) \
                or (i == 51 and hot_keyboard[29] == 1) \
                or (i == 52 and hot_keyboard[30] == 1) \
                or (i == 53 and hot_keyboard[31] == 1) \
                or (i == 54 and hot_keyboard[32] == 1) \
                or (i == 55 and hot_keyboard[33] == 1) \
                or (i == 56 and hot_keyboard[34] == 1) \
                or (i == 57 and hot_keyboard[35] == 1) \
                or (i == 58 and hot_keyboard[36] == 1) \
                or (i == 59 and hot_keyboard[37] == 1) \
                or (i == 60 and hot_keyboard[38] == 1) \
                or (i == 61 and hot_keyboard[39] == 1) \
                or (i == 62 and hot_keyboard[40] == 1) \
                or (i == 63 and hot_keyboard[41] == 1) \
                or (i == 64 and hot_keyboard[42] == 1) \
                or (i == 65 and hot_keyboard[43] == 1) \
                or (i == 66 and hot_keyboard[44] == 1) \
                or (i == 67 and hot_keyboard[45] == 1) \
                or (i == 68 and hot_keyboard[46] == 1) \
                or (i == 69 and hot_keyboard[47] == 1) \
                or (i == 70 and hot_keyboard[48] == 1) \
                or (i == 71 and hot_keyboard[49] == 1) \
                or (i == 72 and hot_keyboard[50] == 1) \
                or (i == 73 and hot_keyboard[51] == 1) \
                or (i == 74 and hot_keyboard[52] == 1) \
                or (i == 75 and hot_keyboard[53] == 1) \
                or (i == 76 and hot_keyboard[54] == 1) \
                or (i == 77 and hot_keyboard[55] == 1) \
                or (i == 78 and hot_keyboard[56] == 1) \
                or (i == 79 and hot_keyboard[57] == 1) \
                or (i == 80 and hot_keyboard[58] == 1) \
                or (i == 81 and hot_keyboard[59] == 1) \
                or (i == 82 and hot_keyboard[60] == 1) \
                or (i == 83 and hot_keyboard[61] == 1) \
                or (i == 84 and hot_keyboard[62] == 1) \
                or (i == 85 and hot_keyboard[63] == 1) \
                or (i == 86 and hot_keyboard[64] == 1) \
                or (i == 87 and hot_keyboard[65] == 1) \
                or (i == 88 and hot_keyboard[66] == 1) \
                or (i == 89 and hot_keyboard[67] == 1) \
                or (i == 90 and hot_keyboard[68] == 1) \
                or (i == 91 and hot_keyboard[69] == 1) \
                or (i == 92 and hot_keyboard[70] == 1) \
                or (i == 93 and hot_keyboard[71] == 1) \
                or (i == 94 and hot_keyboard[72] == 1) \
                or (i == 95 and hot_keyboard[73] == 1) \
                or (i == 96 and hot_keyboard[74] == 1) \
                or (i == 97 and hot_keyboard[75] == 1) \
                or (i == 98 and hot_keyboard[76] == 1) \
                or (i == 99 and hot_keyboard[77] == 1) \
                or (i == 100 and hot_keyboard[78] == 1) \
                or (i == 101 and hot_keyboard[79] == 1) \
                or (i == 102 and hot_keyboard[80] == 1) \
                or (i == 103 and hot_keyboard[81] == 1) \
                or (i == 104 and hot_keyboard[82] == 1) \
                or (i == 105 and hot_keyboard[83] == 1) \
                or (i == 106 and hot_keyboard[84] == 1) \
                or (i == 107 and hot_keyboard[85] == 1) \
                or (i == 108 and hot_keyboard[86] == 1) \
                or (i == 109 and hot_keyboard[87] == 1) \
                or (i == 110 and hot_keyboard[88] == 1) \
                or (i == 111 and hot_keyboard[89] == 1) \
                or (i == 112 and hot_keyboard[90] == 1) \
                or (i == 113 and hot_keyboard[91] == 1) \
                or (i == 114 and hot_keyboard[92] == 1) \
                or (i == 115 and hot_keyboard[93] == 1) \
                or (i == 116 and hot_keyboard[94] == 1) \
                or (i == 117 and hot_keyboard[95] == 1) \
                or (i == 118 and hot_keyboard[96] == 1) \
                or (i == 119 and hot_keyboard[97] == 1) \
                or (i == 120 and hot_keyboard[98] == 1) \
                or (i == 121 and hot_keyboard[99] == 1) \
                or (i == 122 and hot_keyboard[100] == 1) \
                or (i == 123 and hot_keyboard[101] == 1):
                    self.__key_rectangles.append(Rectangle(
                            self.__surface,
                            camera_x + midpoints[i][0] - 10,
                            camera_y + midpoints[i][1] - 10,
                            20 - 2,
                            20 - 2,
                            (0, 200, 0)
                        ))
            if self.__is_cursor_on_left:
                self.__cursor_x = camera_x - vertexX[self.__cursor_i + self.__cursor_j - int(self.__cursor_j / 12)] + 1 - 10
                self.__cursor_y = camera_y + vertexY[self.__cursor_j] + 1 - 10
                self.__cursor = Rectangle(
                    self.__surface,
                    self.__cursor_x,
                    self.__cursor_y,
                    20 - 2,
                    20 - 2,
                    (200, 0, 0)
                )
            else:
                self.__cursor_x = self.__surface.get_width() - (camera_x - vertexX[self.__cursor_i + self.__cursor_j - int(self.__cursor_j / 12)] - 1 + 10)
                self.__cursor_y = camera_y + vertexY[self.__cursor_j] + 1 - 10
                self.__cursor = Rectangle(
                    self.__surface,
                    self.__cursor_x,
                    self.__cursor_y,
                    20 - 2,
                    20 - 2,
                    (200, 0, 0)
                )
        for i in range(row_count + 1):
            y_percent = (i / row_count)
            x = 0
            y = camera_y + ((height - camera_y) * y_percent)
            y_list.append(y)
            self.__polygons.append(Polygon(
                self.__surface,
                x,
                y,
                width,
                y
            ))
        for j in range(column_count + 1):
            x_percent = (j / column_count)
            x = 0 + ((0 + width) * x_percent)
            x_list.append(x)
            y = camera_y
            self.__polygons.append(Polygon(
                self.__surface,
                x,
                y,
                x,
                height
            ))
        for i in range(row_count + 1):
            for j in range(column_count + 1):
                x_percent = (j / column_count)
                y_percent = (i / row_count)
                x = 0 + (width * x_percent)
                self.__last_y = 0
                y = height - ((height / 2) * (1.0 - y_percent))
                self.__polygons.append(Polygon(
                    self.__surface,
                    x_list[i],
                    y_list[j],
                    camera_x,
                    camera_y
                ))
        color_i = 0
        for i in range(row_count + 1):
            for j in range(column_count + 1):
                color_i = color_i + 1
                if color_i > 100:
                    color_i = 0

    def update(self, keyboard_tuple, hot_keyboard):
        self.__cursor_i = (self.__cursor_i + keyboard_tuple[0])
        self.__cursor_j = self.__cursor_j + keyboard_tuple[1]
        if self.__cursor_i >= 10:
                self.__cursor_i = 10
        if self.__cursor_i < 0:
            self.__cursor_i = 0
            # if self.__is_cursor_on_left:
            #     self.__is_cursor_on_left = False
            # else:
            #     self.__is_cursor_on_left = True
        if self.__cursor_i > 120:
            self.__cursor_i = 120
        if self.__cursor_j < 0:
            self.__cursor_j = 0
        if self.__cursor_j > 120:
            self.__cursor_j = 120
        if self.__cursor_j < 24:
            self.__cursor_j = 24
        if self.__cursor_j > 108:
            self.__cursor_j = 108
        if self.__cursor_j == 24 and self.__cursor_i < 3:
            self.__cursor_i = 3
        self.__update_geometry(
            self.__surface.get_width() / 2,
            self.__surface.get_height() / 2,
            hot_keyboard)
            # pygame.mouse.get_pos()[0],
            # pygame.mouse.get_pos()[1])
        for i in range(len(self.__rectangles)):
            self.__rectangles[i].update()
        for key_rectangle in self.__key_rectangles:
            key_rectangle.update()
        self.__cursor.update()
        for i in range(len(self.__texts)):
            self.__surface.blit(
                self.__font2.render(self.__texts[i][0], False, (50, 255, 50)),
                self.__texts[i][1])
        self.__surface.blit(
            self.__font.render(self.__text, False, (255, 255, 255)),
            (self.__cursor_x + 20, self.__cursor_y + 18))
        for i in range(99):
            if i == 0 or i % 10 == 0:
                self.__surface.blit(
                    self.__font.render(str(i),
                        False,
                        (255, 255, 255)),
                    (10 + (i * 10), 85))
        for i in range(323):
            if i < 100:
                self.__surface.blit(
                    self.__font.render(str(pygame.key.get_pressed()[i]),
                        False,
                        (150, 150, 150)),
                    (10 + (i * 10), 100))
            elif i < 200:
                self.__surface.blit(
                    self.__font.render(str(pygame.key.get_pressed()[i]),
                        False,
                        (150, 150, 150)),
                    (10 + ((i - 100) * 10), 115))
            elif i < 300:
                self.__surface.blit(
                    self.__font.render(str(pygame.key.get_pressed()[i]),
                        False,
                        (150, 150, 150)),
                    (10 + ((i - 200) * 10), 130))
            else:
                self.__surface.blit(
                    self.__font.render(str(pygame.key.get_pressed()[i]),
                        False,
                        (150, 150, 150)),
                    (10 + ((i - 300) * 10), 145))


if __name__ == '__main__':
    pygame.init()
    screen = pygame.display.set_mode((500, 500))
    clock = pygame.time.Clock()
    tiles = Tiles(screen, 'black', 'green')
    hot_keyboard = []
    for i in range(200):
        hot_keyboard.append(0)
    while True:
        tiles.update((0, 0), hot_keyboard)
        pygame.display.update()
        clock.tick(60)
