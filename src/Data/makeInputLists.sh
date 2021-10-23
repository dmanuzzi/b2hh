#!/bin/bash

source ${setup_LCG_new}
python ${B2HH_SRC}/Data/makeDATAinputLists.py
python ${B2HH_SRC}/Data/makeMCinputLists.py
