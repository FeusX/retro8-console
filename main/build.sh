#! /bin/zsh

source $HOME/esp/esp-idf/export.sh > /dev/null 2>&1

sudo chmod a+rw /dev/ttyUSB0
cd ~/Documents/retro8-console
idf.py build
idf.py flash monitor
cd main
