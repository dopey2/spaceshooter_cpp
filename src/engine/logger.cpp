#include <iostream>

#define ENABLE_LOGGER 0

namespace Logger {

    void debug(std::string str) {
        #if ENABLE_LOGGER == 1
        std::cout << str << std::endl;
        #endif
    }

    void error(std::string str) {
        std::cerr << str << std::endl;
    }
}