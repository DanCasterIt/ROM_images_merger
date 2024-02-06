#!/bin/bash

# set -x
set -e

INPUT_FILE="${1}"
OUTPUT_FILE='ROM_image.bin'
CNT=0
count=4

for i in $(seq $count)
do
    OUTPUT_FILE_NUM="${OUTPUT_FILE}.$((CNT+1))"
    dd if=${INPUT_FILE} of="${OUTPUT_FILE_NUM}" bs=16k skip=${CNT} count=1
    echo "Done writing: ${OUTPUT_FILE_NUM}"
    du -h "${OUTPUT_FILE_NUM}"
    CNT=$((CNT+1))
done