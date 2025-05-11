#ifndef SYSTEM_H
#define SYSTEM_H
#include <sys/types.h>
#include <unistd.h>

class System {
public:
    enum class PTraceScope {
        NO_RESTRICTIONS,
        RESTRICTED,
        ADMIN_ONLY,
        NO_ATTACH
    };

    static uid_t get_current_user();

    static PTraceScope get_ptrace_scope();
};


#endif //SYSTEM_H
