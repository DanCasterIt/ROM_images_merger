# What does this program
This is a very simple program that takes up to four 16kbyte long files and merges them into a single 64kbyte long file.
The order in wich to concatenate the images can be choosen.
blank spaces will be filled with 0xFF values.

# Why did I make this simple program and what is it thought for
I made this simple program because I erroneously bought some W27C512-45Z EEPROMs for my Acorn BBC Master Compact, an old 8-bit PC.
It has 5 EPROM slots. When buying my W27C512-45Z EEPROMs I didn't know that only the system OS ROM slot is 64kbyte capable and that all the others are only 16kbyte capable exception made for one that is 32kbyte capable.
This means that I should have had buy some D27128 EPROMs instead of W27C512-45Z EEPROMs.

Anyway, since W27C512-45Z are four time bigger than D27128 I decided to unplug the two A13 and A14 address lines from the ROM socket and connect them to a switch to them so that I can switch between 4 ROM images using the same ROM IC. In the Acorn BBC Master Compact PCB A13 and A14 are tied to Vcc. The two switches per ROM IC should connect the two address PINs to GND or Vcc dependinc on which image in the ROM I would like to access.

This tool merges up to four 16kbyte ROM images into a sigle one for a 64kbyte ROM.

# How to compile
gcc 512k_image_generator.c -o 512k_image_generator

# How to use it, example
512k_image_generator EDITROM basiced
Found 2 files. Choose where to place them.
partition 3, @ 0x0000-0x3FFF    ones
partition 2, @ 0x4000-0x7FFF    ones
partition 1, @ 0x8000-0xBFFF    file: basiced
partition 0, @ 0xC000-0xFFFF    file: EDITROM
Apply changes? (y or n): n
Please, select which partition to swap.
Partition number: 1 goes to number: 2
partition 3, @ 0x0000-0x3FFF    ones
partition 2, @ 0x4000-0x7FFF    file: basiced
partition 1, @ 0x8000-0xBFFF    ones
partition 0, @ 0xC000-0xFFFF    file: EDITROM
Apply changes? (y or n): y
Writing "512k_ROM_image.bin"...