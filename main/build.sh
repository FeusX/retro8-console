#! /bin/zsh

source $HOME/esp/esp-idf/export.sh > /dev/null 2>&1

cd ~/Documents/esp32-console
idf.py build
idf.py flash monitor
cd main
