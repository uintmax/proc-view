#include <iostream>
#include "Process.h"

int main() {
    try {
        Process proc(1);
        std::cout << "uid: " << proc.get_uid() << std::endl;

        auto proc_list = Process::get_all_processes();
        for (const auto &proc_entry: proc_list) {
            std::cout << "[" << proc_entry.get_pid() << "] uid: " << proc_entry.get_uid() << std::endl;
        }
        std::cout << "size: " << proc_list.size() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}
