import os
import random
import sys


KEYWORD = 'Cloud'

def get_filename(path: str) -> str:
    length = 0
    cloud_filenames = []
    for root, directory, filenames in os.walk(path):
        for filename in filenames:
            if KEYWORD in filename:
                cloud_filenames.append(filename)
                length += 1
    length = random.randint(0, length - 1)
    return cloud_filenames[length]


def get_path() -> str:
    path = ''
    if os.name == 'posix' and sys.platform == 'darwin':
        path += os.path.join(
            os.sep,
            'Applications',
            'PureBasic.app',
            'Contents',
            'Resources',
            'examples',
            '3d',
            'Data',
            'Textures')
    elif os.name == 'posix':
        path += os.path.join(
            os.sep,
            'home',
            os.getlogin(),
            'Desktop',
            'sensoryRoom',
            'textures')
        # path = ''
    elif socket.gethostname() == 'DESKTOP-CR5GQ2G':
        path += os.path.join(
            'C:',
            os.sep,
            'Users',
            os.getlogin(),
            'OneDrive',
            'Desktop',
            'PureBasic',
            'Examples',
            '3D',
            'Data',
            'Textures')
    elif socket.gethostname() == 'terrortronics':
        path = str(pathlib.Path().resolve()) + os.sep + 'textures'
    else:
        path += os.path.join(
            'C:',
            os.sep,
            'Users',
            os.getlogin(),
            'Desktop',
            'PureBasic',
            'Examples',
            '3D',
            'Data',
            'Textures')
    return path


if __name__ == '__main__':
    get_filename('./')
    get_path()
