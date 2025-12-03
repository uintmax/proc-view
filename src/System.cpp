#include "System.h"

namespace sys {
    uid_t get_current_user() {
        return getuid();
    }

    PTraceScope get_ptrace_scope() {
        // TODO: Check if file does not exist -> exception
        std::ifstream ptrace_ifstream(ptrace_scope_path);
        std::stringstream ptrace_str_stream;
        std::string ptrace_scope_str;
        ptrace_str_stream << ptrace_ifstream.rdbuf();
        ptrace_scope_str = ptrace_str_stream.str();

        // Second char is a newline character
        if (ptrace_scope_str.empty() || ptrace_scope_str.length() != 2)
            throw std::runtime_error("Unexpected ptrace scope");
        int mode = std::stoi(ptrace_scope_str);
        if (mode < 0 || mode >= static_cast<int>(PTraceScope::COUNT))
            throw std::runtime_error("Unexpected ptrace scope");
        PTraceScope ptrace_scope{mode};
        return ptrace_scope;
    }
}
