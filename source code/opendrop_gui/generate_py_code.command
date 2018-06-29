#!/bin/bash
cd "$(dirname "$0")"
sudo pyuic5 -x opendrop_gui.ui -o opendrop_gui.py -x
sudo chmod 777 opendrop_gui.py
