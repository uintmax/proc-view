#define SOL_ALL_SAFETIES_ON 1
#include <iostream>
#include "Process.h"
#include "System.h"
#include <sol/sol.hpp>
#include <QtWidgets>

#include "analysis/MemoryScanner.h"
#include "analysis/StringsFinder.h"
#include "analysis/LuaInterface.h"
#include "ui/ProcListWindow.h"

int main(int argc, char **argv) {
    analysis::LuaInterface lua_interface{};
    lua_interface.execute_script(R"(
    procs = get_processes()
    for k,v in pairs(procs) do
        print(v:get_pid() .. " - " .. v:get_name())
    end
    )"
    );


    return 0;
    auto proc = Process::get_process_by_name("test-bin");
    analysis::StringsFinder strings_finder{proc};

    for (const auto &str: strings_finder.find()) {
        std::cout << str << std::endl;
    }

    /*
    analysis::MemoryScanner memory_scanner{proc};
    memory_scanner.scan_new<uint32_t>(1000);
    for (const auto &addr: memory_scanner.get_addr_results()) {
        std::cout << std::hex << addr << std::endl;
    }

    getchar();
    memory_scanner.scan_next<uint32_t>(54321);
    for (const auto &addr: memory_scanner.get_addr_results()) {
        std::cout << std::hex << addr << std::endl;
    }
    */

    return 0;
    QApplication app(argc, argv);

    ui::ProcListWindow proc_list_window;


    return app.exec();


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
