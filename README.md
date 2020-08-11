# What does this program
This program creates a file made of n partitions equally sized and puts in these partitions the files specified in the arguments.
Blank spaces will be filled with 0xFF values.
The user can choose:
* which file goes in each partition
* the lenght of the final image
* the number of partitions

# Why did I make this program and what is it thought for
I made this simple program because I erroneously bought some W27C512-45Z EEPROMs for my Acorn BBC Master Compact, an old 8-bit PC.
It has 5 EPROM slots. When buying my W27C512-45Z EEPROMs I didn't know that only the system OS ROM slot is 64kbyte capable and that all the others are only 16kbyte capable exception made for one that is 32kbyte capable.
This means that I should have had buy some D27128 EPROMs instead of W27C512-45Z EEPROMs.

Anyway, since W27C512-45Z are four time bigger than D27128 I decided to unplug the two A13 and A14 address lines from the ROM socket and connect a switch to them so that I can switch between 4 ROM images using the same ROM IC. In the Acorn BBC Master Compact PCB A13 and A14 are tied to Vcc. The two switches per ROM IC should connect the two address PINs to GND or Vcc depending on which image in the ROM I would like to access.

This tool is thought to merge four 16kbyte ROM images into a sigle one for a 64kbyte ROM but these parameters can be modified.

# How to compile
gcc ROM_image_generator.c -o ROM_image_generator

It works both in Linux and Windows. A 32-bit Windows binary is provided in this repo.

# How to use it, example
```
ROM_image_generator DFSimage EDITROM basiced
Please, specify the memory size in bytes. (0 for 65536): 0
Please, specify the number of equally sized partitions. (0 for 4): 0
Found 3 files. Choose where to place them.
partition 3 @ 0x00000000-0x00003FFF filled with ones
partition 2 @ 0x00004000-0x00007FFF filled with file: basiced
partition 1 @ 0x00008000-0x0000BFFF filled with file: EDITROM
partition 0 @ 0x0000C000-0x0000FFFF filled with file: DFSimage
Apply changes? (y or n): n
Please, select which partition to swap.
Partition number: 1
goes to number: 3
partition 3 @ 0x00000000-0x00003FFF filled with file: EDITROM
partition 2 @ 0x00004000-0x00007FFF filled with file: basiced
partition 1 @ 0x00008000-0x0000BFFF filled with ones
partition 0 @ 0x0000C000-0x0000FFFF filled with file: DFSimage
Apply changes? (y or n): y
Writing "ROM_image.bin"...
```