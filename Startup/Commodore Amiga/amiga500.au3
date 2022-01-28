import subprocess

from tkinter import messagebox

cmd = "/usr/bin/fs-uae"

messagebox.showinfo("Amiga 500 starter...", cmd)

returned_value = subprocess.call(cmd, shell=True)
print('returned value;', returned_value)
