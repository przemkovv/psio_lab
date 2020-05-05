#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

struct Block {
    bool bit = false;
    int count = 0;
};

std::ostream& operator<<(std::ostream& out, const Block& blockee) {
    if (blockee.bit) {
        out << "0";
    }
    else {
        out << "00";
    }
    out << " ";
    auto count = blockee.count;
    while (count--) {
        out << "0";
    }
    return out;
}


int main()
{
    std::string MESSAGE;
    std::getline(std::cin, MESSAGE);
    std::cerr << MESSAGE << std::endl;
    std::vector<Block> blocks;
    Block block;

    for (char character : MESSAGE) {
        std::cerr << character << std::endl;
        for (int bitIndex = 0; bitIndex < 7; ++bitIndex) {
            if (character & 0x40) {
                std::cerr << "YAY" << std::endl;
                if (block.bit == false && block.count) {
                    blocks.push_back(block);
                    block.count = 0;
                }
                block.bit = true;
                ++block.count;
            }
            else {
                std::cerr << "NOPE" << std::endl;
                if (block.bit == true && block.count) {
                    blocks.push_back(block);
                    block.count = 0;
                }
                block.bit = false;
                ++block.count;
            }
            character <<= 1;
        }
    }
    blocks.push_back(block);

    std::cerr << blocks.size() << std::endl;
    std::stringstream out_stream;
    for (const Block& block : blocks) {
        out_stream << block;
        out_stream << " ";
    }
    std::string out_string = out_stream.str();
    out_string.pop_back();
    std::cout << out_string;

}