#!/bin/bash
# Program:
#   This program shows the user's choice
# History:
# 2022/01/16  Octobug First release
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

read -p "Please input (Y/N): " yn
[[ "$yn" == "Y" || "$yn" == "y" ]] && echo "OK, continue" && exit 0
[[ "$yn" == "N" || "$yn" == "n" ]] && echo "Oh, interrupt!" && exit 0
echo "I don't know what your choice is" && exit 1
