#!/bin/bash

set -x
set -e

g++ -std=c++11 ROM_image_generator_v2.cpp -o ROM_image_generator_v2

./ROM_image_generator_v2 FILE1 FILE2 FILE3 FILE4 FILE5
./ROM_image_generator_v2 FILE1 FILE2 FILE3 FILE4 FILE5 -t 8 -n 2
./ROM_image_generator_v2 -t 8 -n 2 FILE1 FILE2 FILE3 FILE4 FILE5
./ROM_image_generator_v2 FILE1 FILE2 -1 -0 FILE5
./ROM_image_generator_v2 FILE1 FILE2 -1 -0 FILE5 -t || true # Throw an error because of incomplete paramiter
./ROM_image_generator_v2 FILE1 FILE2 -1 -0 FILE5 -o supercalifragilistichespiralitoso.bin # Set the output filename