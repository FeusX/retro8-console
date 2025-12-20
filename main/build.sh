#! /bin/zsh

source $HOME/esp/esp-idf/export.sh > /dev/null 2>&1

sudo chmod a+rw /dev/ttyUSB0
cd ~/Documents/esp32-console
idf.py build
idf.py flash monitor
cd main
