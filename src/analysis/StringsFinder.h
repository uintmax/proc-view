#ifndef STRINGSFINDER_H
#define STRINGSFINDER_H

#include "../Process.h"
#include <vector>
#include <string>
#include <cctype>

namespace analysis {
    /**
     * Finds null-terminated strings in given process
     */
    class StringsFinder {
    public:
        StringsFinder(Process &proc, uint32_t min_len = 10, uint32_t max_len = 50): proc(proc), min_len(min_len),
            max_len(max_len) {
        }

        std::vector<std::string> find();

    private:
        Process proc;
        uint32_t min_len;
        uint32_t max_len;

        static constexpr size_t mib = 1024 * 1024;
        static constexpr size_t buffer_size = mib * 100;
    };
}


#endif //STRINGSFINDER_H
