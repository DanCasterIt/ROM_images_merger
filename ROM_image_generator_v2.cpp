#include <iostream>
#include <iomanip>
#include <list>

#define DEBUG 1

// compile this file using the command `g++ -std=c++11 ROM_image_generator_v2.cpp -o ROM_image_generator_v2`

using namespace std;

enum filler {
    ZEROS = 0,
    ONES = 1,
    IMAGE = 2
};

struct image    {
    string name;
    uint32_t start;
    uint32_t end;
    filler fllr; 
};

struct memParams    {
    memParams(uint32_t totalSize, uint32_t totalPartitionsNumber)
        : totalSize(totalSize),
        partitionSize(0),
        totalPartitionsNumber(totalPartitionsNumber)
    {}

    uint32_t totalSize;
    uint32_t partitionSize;
    uint32_t totalPartitionsNumber;
};

class romImageGenerator {
public:
    romImageGenerator(memParams &mpar)
        : imgs(list<image>()),
        mpar(mpar),
        outFileName("ROM_image.bin")
    {}

    bool parseCMDLineParams(int &argc, char ** &argv)   {
        if(argc <= 1)
            return 1;

        for(int i = 1; i < argc; i++)   {
            if(string(argv[i]) == "-t")    {
                i++;
                if(i >= argc)
                    return 1;
                mpar.totalSize = stoi(string(argv[i]), 0, 10);
            } else if(string(argv[i]) == "-o") {
                outFileName = string(argv[i]);
            } else if(string(argv[i]) == "-n") {
                i++;
                if(i >= argc)
                    return 1;
                mpar.totalPartitionsNumber = stoi(string(argv[i]), 0, 10);
            } else if(string(argv[i]) == "-1") {
                image img;
                img.name = string("0xFF");
                img.fllr = ONES;
                imgs.push_back(img);
            } else if(string(argv[i]) == "-0") {
                image img;
                img.name = string("0x00");
                img.fllr = ZEROS;
                imgs.push_back(img);
            } else {
                image img;
                img.name = string(argv[i]);
                img.fllr = IMAGE;
                imgs.push_back(img);
            }
        }

        if(mpar.totalPartitionsNumber <= 0)
            mpar.totalPartitionsNumber = imgs.size();
        if(mpar.totalSize > 0 && mpar.totalPartitionsNumber > 0)
            mpar.partitionSize = mpar.totalSize / mpar.totalPartitionsNumber;
        else
            return 1; // ask the user to provide the missing paramiter instead!

#if DEBUG
        cout << "totalSize = 0x" << setfill('0') << setw(8) << right << hex << mpar.totalSize;
        cout << ", partitionSize = 0x"<< setfill('0') << setw(8) << right << hex << mpar.partitionSize;
        cout << ", totalPartitionsNumber = " << mpar.totalPartitionsNumber;
        cout << ", outFileName = " << outFileName << endl;
#endif

        uint32_t e = 0;
        for(auto &img : imgs)   { // modify it to remove extra images or add blank images through a menu if the user didn't provide enough files...
            img.start = e * mpar.partitionSize;
            img.end = (e * mpar.partitionSize) + mpar.partitionSize;
            e++;
        }

        return 0;
    }

    void printImageLayout() {
        int i = 0;
        for(auto img : imgs) {
            if(i >= mpar.totalPartitionsNumber)
                break;
            cout << "partition " << i << " @ ";
            cout << "0x" << setfill('0') << setw(8) << right << hex << img.start;
            cout << " - 0x" << setfill('0') << setw(8) << right << hex << img.end;
            cout << " = " << img.name << endl;
            i++;
        }
    }

private:
    list<image> imgs;
    memParams &mpar;
    string outFileName;
};

int main(int argc, char *argv[])  {
    memParams mpar(0xFFFF, 4); // Default params
    romImageGenerator rig(mpar);

    if(rig.parseCMDLineParams(argc, argv))  {
        cout << "Error encountered when parsing command line paramiters" << endl;
        return -1;
    }
    rig.printImageLayout();
    return 0;
}