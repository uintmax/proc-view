#include "MemoryScanner.h"

namespace analysis {
    std::vector<uintptr_t> MemoryScanner::get_addr_results() const {
        return addr_results;
    }

    void MemoryScanner::reset() {
        addr_results.clear();
    }
}
