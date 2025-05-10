#include <iostream>
#include "Process.h"

int main() {
    try {
        Process proc(1);
        std::cout << "uid: " << proc.get_uid() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}
