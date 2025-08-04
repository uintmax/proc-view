#include "LuaInterface.h"

namespace analysis {
    LuaInterface::LuaInterface() {
        lua.open_libraries(sol::lib::base);
        lua.new_usertype<Process>("Process", sol::constructors<Process(pid_t pid)>(),
                                  "get_pid", &Process::get_pid,
                                  "get_name", &Process::get_comm);

        lua.set_function("get_processes", Process::get_all_processes);
    }

    void LuaInterface::execute_script(const std::string &script) {
        lua.script(script);
        /*
        lua.script(R"(
        procs = get_processes()
        for k,v in pairs(procs) do
            print(v:get_pid() .. " - " .. v:get_name())
        end
)");
*/
    }
}
