#include <iostream>

#define ENABLE_LOGGER 1

namespace Logger {

void debug(const std::string& str) {
#if ENABLE_LOGGER == 1
    std::cout << str << std::endl;
#endif
}

void error(const std::string& str) { std::cerr << str << std::endl; }
} // namespace Logger