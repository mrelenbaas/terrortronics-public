#!/usr/bin/python3

import sys
import os

if len(sys.argv)!=4:
    print("requires 3 arguments. <source_file> <dest_file> <symbol_name>")
    print("bin2h textures/meteor.png compiled/meteor.h meteor")
    exit(-1)

source_filename  = sys.argv[1]
dest_filename  = sys.argv[2]
symbol_name = sys.argv[3]

if not os.path.exists(source_filename):
    print("Unable to  find file {}".format(source_filename))
    exit(-1)

with open(dest_filename,'w') as ofile:
    ofile.write("#pragma once\n\n")
    ofile.write("const unsigned char {}[] = {{".format(symbol_name))
    idx = 0
    size = os.path.getsize(source_filename)
    with open(source_filename, 'rb') as ifile:
        for idata in ifile.read():
            if idx % 16==0:
                ofile.write('\n\t')
            idx=idx+1
            if (idx<size):
                ofile.write('0x%02X,' % idata)
            else:
                ofile.write('0x%02X' % idata)

    ofile.write('\n};')

