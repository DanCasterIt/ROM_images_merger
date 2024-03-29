# What does this program
This program creates a file made of n partitions equally sized and puts in these partitions the files specified in the arguments. Blank spaces will be filled with `0xFF` or `0x00` values.
The user can choose:
* which file goes in each partition
* the lenght of the final image
* the number of partitions

# Why did I make this program and what is it thought for
I made this simple program because I erroneously bought some `W27C512-45Z` EEPROMs for my Acorn BBC Master Compact, an old 8-bit PC.
It has 5 EPROM slots. When buying my `W27C512-45Z` EEPROMs I didn't know that only the system OS ROM slot is 64kbyte capable and that all the others are only 16kbyte capable exception made for one that is 32kbyte capable.
This means that I should have had buy some `D27128` EPROMs instead of `W27C512-45Z` EEPROMs.

Anyway, since `W27C512-45Z` are four time bigger than `D27128` I decided to unplug the two `A13` and `A14` address lines from the ROM socket and connect a switch to them so that I can switch between 4 ROM images using the same ROM IC. In the Acorn BBC Master Compact PCB `A13` and `A14` are tied to `Vcc`. The two switches per ROM IC should connect the two address `PIN`s to `GND` or `Vcc` depending on which image in the ROM I would like to access.

This tool is thought to merge four 16kbyte ROM images into a sigle one for a 64kbyte ROM but these parameters can be modified.

# How to compile
```bash
gcc ROM_image_generator.c -o ROM_image_generator
```

Tested in Linux, Windows and MacOS. \
A 32-bit Windows binary `ROM_image_generator.exe` is provided in this repo toghether with an Apple silicon M1 one `ROM_image_generator.macM1`.

# How to use it, example
```
$ ./ROM_image_generator utils basic48 adfs210
Input the memory size in bytes. (0 for 65536): 0
Input the number of equally sized partitions. (0 for 4): 0
Input if to fill blank partitions with ones (1) or zeros (0): 1
Found 3 files. Choose where to place them.
partition 0 @ 0x00000000-0x00003FFF filled with file: adfs210
partition 1 @ 0x00004000-0x00007FFF filled with file: basic48
partition 2 @ 0x00008000-0x0000BFFF filled with file: utils
partition 3 @ 0x0000C000-0x0000FFFF filled with FFs
Apply changes? (y or n): n
Input which partition to swap.
Partition number: 3
goes to number: 1
partition 0 @ 0x00000000-0x00003FFF filled with file: adfs210
partition 1 @ 0x00004000-0x00007FFF filled with FFs
partition 2 @ 0x00008000-0x0000BFFF filled with file: utils
partition 3 @ 0x0000C000-0x0000FFFF filled with file: basic48
Apply changes? (y or n): y
Writing "ROM_image.bin"...
```

Then if using a TL866II+ programmer with the `minipro` command line tool, the immage can be flashed with the command
```bash
minipro -s -p "W27C512@DIP28" -w ROM_image.bin
```
The `-m` option can be used in place of `-w` to verify that the write process completed correctly. \
Compatible devices can be listed using the `-L` option like in the following example
```
$ minipro -L W27C512
No TL866 device found. Which database do you want to display?
1) TL866A
2) TL866II+
3) Abort
2
W27C512@DIP28
W27C512@PLCC32
```

# Bash script version of this program
Bash versions of this program plus one that splits a 64Kbyte image into four 16Kbyte images can be found in the `bashVersion/` folder in the root directory of this repository.

# PCB projects I made using this tool
- [Acorn BBC Master compact cartridge](https://oshwlab.com/black__man/acorn-bbc-master-compact-cartridge)
- [Acorn BBC Master compact cartridge ZIF ](https://oshwlab.com/black__man/acorn-bbc-master-compact-cartridge_copy)
- [Acorn BBC Master Compact 128K system ROM](https://oshwlab.com/black__man/acorn-bbc-master-compact-128k-system-rom)