#!/usr/bin/env python
# Author: Bradley Elenbaas
# Copyright 2023 Bradley Elenbaas
# License: GPL v3

#!/usr/bin/env python

# C:\Users\[USERNAME]\AppData\Roaming\GIMP\2.10\plug-ins

from gimpfu import *
import os.path
pdb = gimp.pdb
import sys
#sys.stderr = open("C:\\tmp\\gimp_python_errs.txt",'a')

# this is the bit that does all the work
def save_every_layer(Image, Drawable):
  for layer in Image.layers:
    if 'Outline' in layer.name:
      continue
    if 'Background' in layer.name:
      continue
    CurrentFilePath = Image.filename + layer.name
    RootFilePath = os.path.splitext(CurrentFilePath)[0]
    RootFilePath = RootFilePath.split(os.sep)[-1]
    #PNGFilePath = RootFilePath+".png"
    PNGFilePath = "C:\\Users\\mrele\\Drawing Importer\\Assets\\Textures\\"+RootFilePath+layer.name.replace(' ', '').replace('-', '')+".png"
    pdb.gimp_file_save(Image, layer, PNGFilePath, PNGFilePath)
  
#  Image.clean_all()  # Uncomment this to avoid the save warning but YOU accept the risk of loosing work.
  
# menu registration
register(
    "python-fu-save_every_layer",
    "save_every_layer Export this image to PNG",
    "save_every_layer",
    "save_every_layer",
    "GimpChat",
    "2023/01/19",
    "Export PNG for save_every_layer",
    "*",
    [
      (PF_IMAGE, "Image", "Chose Image", None),
      (PF_DRAWABLE, "Drawable", "Chose Drawable", None)
    ],
    [],
    save_every_layer,
    menu="<Image>/File"
    )

main()
