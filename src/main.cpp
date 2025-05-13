#include <iostream>
#include "Process.h"
#include "System.h"

int main() {
    try {
        Process proc(1);
        std::cout << "uid: " << proc.get_uid() << std::endl;

        auto proc_list = Process::get_all_processes();
        for (const auto &proc_entry: proc_list) {
            std::cout << "[" << proc_entry.get_pid() << "] uid: " << proc_entry.get_uid() << std::endl;
            if (proc_entry.get_uid() == System::get_current_user()) {
                try {
                    std::cout << proc_entry.get_exe() << std::endl;
                } catch (const std::exception &e) {
                    // TODO: Check for zombie/defunct processes
                    std::cerr << e.what() << std::endl;
                }
            }
        }
        std::cout << "size: " << proc_list.size() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    Process test_proc(26465);
    auto test_val = test_proc.read<int>(0x7ffffe2ffedc);
    std::cout << "test value: " << test_val << std::endl;

    return 0;
}
