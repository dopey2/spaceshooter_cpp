#include <iostream>

namespace Logger {

    void debug(std::string str) {
        std::cout << str << std::endl;
    }

    void error(std::string str) {
        std::cerr << str << std::endl;
    }
}