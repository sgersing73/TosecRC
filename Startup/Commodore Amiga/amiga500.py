#!/usr/bin/python3
"""
Startup script for FS-UAE
"""

import subprocess
import sys

from tkinter import messagebox

KICKSTART = ' --kickstart_file="Kickstart v3.1 r40.063 (1993-07)(Commodore)(A500-A600-A2000)[!].rom"'
CMD = '/usr/bin/fs-uae'

for eachArg in sys.argv:
    if '/b:' in eachArg:
        rom = eachArg[3:]

CMD = CMD + ' --floppy-drive-0="' + rom + '"' + KICKSTART

RETVAL = subprocess.call(CMD, shell=True)

print('returned value;', RETVAL)
