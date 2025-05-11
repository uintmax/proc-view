#include "System.h"

uid_t System::get_current_user() {
    return getuid();
}

