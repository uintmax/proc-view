#ifndef MEMORYSCANNER_H
#define MEMORYSCANNER_H

#include "../Process.h"


namespace analysis {
    /**
     * Scans memory regions of the given process for (changing) values
     */
    class MemoryScanner {
    public:
        MemoryScanner(const Process &proc): proc(proc) {
        }

        template<typename T>
        void scan_new(T value) {
            reset();
            for (const auto &region: proc.get_memory_regions()) {
                // Can not read [vvar] memory region
                if (region.get_pathname() == "[vvar]")
                    continue;
                if (region.is_readable() && !region.is_executable()) {
                    auto read_addr = region.get_start_addr();
                    while (read_addr < region.get_end_addr()) {
                        auto region_space = region.get_end_addr() - region.get_start_addr();
                        auto read_size = std::min(buffer_size, region_space);
                        std::vector<uint8_t> buffer(read_size);
                        proc.read(read_addr, buffer);
                        for (int i = 0; i < buffer.size(); i += sizeof(T)) {
                            if (value == *reinterpret_cast<T *>(&buffer[i])) {
                                addr_results.push_back(read_addr + i);
                            }
                        }
                        read_addr += read_size;
                    }
                }
            }
        }

        // Maybe set template type at class
        template<typename T>
        void scan_next(T value) {
            T buffer;
            std::erase_if(addr_results, [this, &buffer, &value](const auto &addr) {
                try {
                    proc.read(addr, buffer);
                } catch (std::runtime_error &e) {
                    return true;
                }
                return buffer != value;
            });
        }

        void reset();


        std::vector<uintptr_t> get_addr_results() const;

    private:
        static constexpr size_t mib = 1024 * 1024;
        static constexpr size_t buffer_size = mib * 100;
        Process proc;
        std::vector<uintptr_t> addr_results;
    };
}


#endif //MEMORYSCANNER_H
