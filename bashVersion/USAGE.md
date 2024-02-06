# Usage example
Usage examples of `merge.sh` and `split.sh`

These scripts are written specifically to handle 64Kbyte (27512 EPROMs) images only, they are not as flexible as the C program in the root directory of this repository but they can be easily modified for different ROM sizes

## Usage of `merge.sh`
```bash
./merge.sh os51 adfs210 basic48 utils
```
The output will be
```
Processing file "os51"...
1+0 records in
1+0 records out
16384 bytes transferred in 0.000441 secs (37151927 bytes/sec)
Processing file "adfs210"...
1+0 records in
1+0 records out
16384 bytes transferred in 0.000412 secs (39766990 bytes/sec)
Processing file "basic48"...
1+0 records in
1+0 records out
16384 bytes transferred in 0.000186 secs (88086022 bytes/sec)
Processing file "utils"...
1+0 records in
1+0 records out
16384 bytes transferred in 0.000524 secs (31267176 bytes/sec)
Done writing "ROM_image.bin"
 64K    ROM_image.bin
```
It will write the images specified in the command line in the order from left to right

## Usage of `split.sh`
```bash
./split.sh 27512\@DIP28.BIN
```
The output will be
```
1+0 records in
1+0 records out
16384 bytes transferred in 0.000879 secs (18639363 bytes/sec)
Done writing: ROM_image.bin.1
 16K    ROM_image.bin.1
1+0 records in
1+0 records out
16384 bytes transferred in 0.000353 secs (46413598 bytes/sec)
Done writing: ROM_image.bin.2
 16K    ROM_image.bin.2
1+0 records in
1+0 records out
16384 bytes transferred in 0.000130 secs (126030769 bytes/sec)
Done writing: ROM_image.bin.3
 16K    ROM_image.bin.3
1+0 records in
1+0 records out
16384 bytes transferred in 0.000295 secs (55538983 bytes/sec)
Done writing: ROM_image.bin.4
 16K    ROM_image.bin.4
```