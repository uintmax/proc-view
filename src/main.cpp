#define SOL_ALL_SAFETIES_ON 1
#include <iostream>
#include "Process.h"
#include "System.h"
#include <sol/sol.hpp>
#include <QtWidgets>

int main(int argc, char **argv) {

    QApplication app(argc, argv);
    QWidget window;
    window.resize(600, 600);
    window.show();
    return app.exec();

    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua.new_usertype<Process>("Process", sol::constructors<Process(pid_t pid)>(),
                              "get_pid", &Process::get_pid,
                              "get_name", &Process::get_comm);

    lua.set_function("get_processes", Process::get_all_processes);
    lua.script("print('hello :D')");
    lua.script(R"(
        procs = get_processes()
        for k,v in pairs(procs) do
            print(v:get_pid() .. " - " .. v:get_name())
        end
)");

    /*
    auto proc = Process::get_process_by_name("test-bin");
    auto memory_regions = proc.get_memory_regions();
    for (const auto &memory_region: memory_regions) {
        if (memory_region.is_executable()) {
            std::cout << std::hex << memory_region.get_start_addr() << " - " << memory_region.get_end_addr() << " " <<
                    memory_region.get_pathname() << std::endl;
        }
    }
    */

    return 0;
}
