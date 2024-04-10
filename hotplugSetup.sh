#!/bin/bash
# Should be run before the USB device attach
# Details: https://github.com/dorssel/usbipd-win/wiki/WSL-support

sudo service udev restart
sudo udevadm control --reload
