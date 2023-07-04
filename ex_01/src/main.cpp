#include <iostream>
#include "../include/RPN.hpp"

#define ERR_USAGE "Usage: ./RPN [input_string]"
int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << ERR_USAGE << std::endl;
    }
    RPN rpn(argv[1]);
}