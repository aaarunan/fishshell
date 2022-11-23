#!/usr/bin/env python3
from pathlib import Path
import os

home = Path.home()
shell_dir = '/home/arunang/dev/shell'

def get_shellrc_path():
    shell = os.environ["SHELL"]
    rcs = {
        "/usr/bin/bash": ".bashrc",
        "/usr/bin/zsh": ".zshrc",
        "/usr/bin/fish": ".fishrc",
    }

    rc = rcs.get(shell)
    if rc is None:
        raise ValueError(f"The shell {shell} is unknown")
    return home/rc


def change_rc():
    with open(get_shellrc_path(), 'a') as f:
        f.writelines([f"cd {shell_dir} \n", "./shell"])

if __name__=='__main__':
    change_rc()

