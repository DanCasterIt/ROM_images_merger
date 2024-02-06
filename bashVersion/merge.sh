#!/bin/bash

# set -x
set -e

OUTPUT_FILE='ROM_image.bin'
CNT=0

for FILE in "$@"
do
    echo "Processing file \"${FILE}\"..."
    dd if="${FILE}" of="${OUTPUT_FILE}" bs=16k oseek=$CNT
    CNT=$((CNT+1))
done

echo "Done writing \"${OUTPUT_FILE}\""
du -h "${OUTPUT_FILE}"