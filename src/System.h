#ifndef SYSTEM_H
#define SYSTEM_H
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace sys {
    enum class PTraceScope {
        SAME_UID = 0,
        RESTRICTED,
        ADMIN_ONLY,
        NO_ATTACH,
        COUNT
    };

    const std::string ptrace_scope_path = "/proc/sys/kernel/yama/ptrace_scope";

    uid_t get_current_user();

    PTraceScope get_ptrace_scope();
};


#endif //SYSTEM_H
