#!/usr/bin/env python
# Author: jaftwo
# Copyright 2017 jaftwo
# License: GPL v3
# GIMP plugin to export the current image as .png
# For jaftwo:- http://gimpchat.com/viewtopic.php?f=8&t=15154

'''
https://gimplearn.net/viewtopic.php?t=426
1) Download file and unzip if it is zipped so that you get file with .py extension.
2) Inside GIMP program, go to Edit -> Preferences -> Folders -> Plug-Ins and see the folder/path listed.
3) Copy/Move the .py file from step 1 to one of one of those folders.
4) If you're on Linux, you'll have to browse to the file and right click on it, the Properties, Permissions Tab, Allow Execute as Program (to make it executable).
5) Restart GIMP.
6) And now plug-in is active for use.
'''

from gimpfu import *
import os.path
pdb = gimp.pdb
import sys
#sys.stderr = open("C:\\tmp\\gimp_python_errs.txt",'a')

# this is the bit that does all the work
def jaftwo001(Image, Drawable):
  CurrentFilePath = Image.filename
  RootFilePath = os.path.splitext(CurrentFilePath)[0]
  RootFilePath = RootFilePath.split(os.sep)[-1]
  #PNGFilePath = RootFilePath+".png"
  PNGFilePath = "C:\\Users\\mrele\\SoftfootFalls\\Assets\\Textures\\"+RootFilePath+".png"
  pdb.gimp_file_save(Image, Drawable, PNGFilePath, PNGFilePath)
  
#  Image.clean_all()  # Uncomment this to avoid the save warning but YOU accept the risk of loosing work.

  # The End of the main routine
  
# menu registration
register(
    "python-fu-jaftwo001",
    "jaftwo Export this image to PNG",
    "jaftwo",
    "jaftwo",
    "GimpChat",
    "2017/01/03",
    "Export PNG for jaftwo",
    "*",
    [
      (PF_IMAGE, "Image", "Chose Image", None),
      (PF_DRAWABLE, "Drawable", "Chose Drawable", None)
    ],
    [],
    jaftwo001,
    menu="<Image>/File"
    )

main()
