#ifndef LUAINTERFACE_H
#define LUAINTERFACE_H

#include "../Process.h"

#include <sol/sol.hpp>

namespace analysis {
    /**
     * Executes given Lua scripts
     * Lua scripts have access to the Process class
     */
    class LuaInterface {
    public:
        LuaInterface();

        // TODO: Add return type, for now only info on stdout
        void execute_script(const std::string &script);

    private:
        sol::state lua{};
    };
}


#endif //LUAINTERFACE_H
