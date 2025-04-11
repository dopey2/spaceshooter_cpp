#include <iostream>

#define ENABLE_LOGGER 1

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