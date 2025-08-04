#ifndef MEMORYREGION_H
#define MEMORYREGION_H
#include <cstdint>
#include <utility>
#include <string>
#include <ranges>
#include <vector>
#include <charconv>


class MemoryRegion {
public:
    MemoryRegion(const std::string &maps_entry);

    uintptr_t get_start_addr() const;

    uintptr_t get_end_addr() const;

    bool is_readable() const;

    bool is_writable() const;

    bool is_executable() const;

    std::string get_permissions() const;

    std::string get_pathname() const;

private:
    uintptr_t start_addr;
    uintptr_t end_addr;
    bool readable;
    bool writable;
    bool executable;
    std::string permissions;
    std::string pathname;
};


#endif //MEMORYREGION_H
