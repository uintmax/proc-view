#include "MemoryRegion.h"


MemoryRegion::MemoryRegion(const std::string &maps_entry) {
    // ranges::to is relatively new: https://en.cppreference.com/w/cpp/compiler_support.html
    auto elems = maps_entry | std::views::split(' ') | std::views::filter(
                     [](auto elem) { return !elem.empty(); }) |
                 std::ranges::to<std::vector<std::string> >();

    auto addr_elem = elems.at(0);
    auto addresses = addr_elem | std::views::split('-') | std::ranges::to<std::vector<std::string> >();
    auto &start_addr_str = addresses.at(0);
    auto &end_addr_str = addresses.at(1);
    auto res_start = std::from_chars(start_addr_str.data(), start_addr_str.data() + start_addr_str.size(),
                                     start_addr, 16);
    if (res_start.ec != std::errc{} || res_start.ptr != start_addr_str.data() + start_addr_str.size()) {
        throw std::runtime_error("Could not parse start address");
    }

    auto res_end = std::from_chars(end_addr_str.data(), end_addr_str.data() + end_addr_str.size(),
                                   end_addr, 16);
    if (res_end.ec != std::errc{} || res_end.ptr != end_addr_str.data() + end_addr_str.size()) {
        throw std::runtime_error("Could not parse end address");
    }

    auto permissions = elems.at(1);
    readable = permissions.at(0) != '-';
    writable = permissions.at(1) != '-';
    executable = permissions.at(2) != '-';

    pathname = elems.size() == 6 ? elems.at(5) : "empty";
}

uintptr_t MemoryRegion::get_start_addr() const {
    return start_addr;
}

uintptr_t MemoryRegion::get_end_addr() const {
    return end_addr;
}

bool MemoryRegion::is_readable() const {
    return readable;
}

bool MemoryRegion::is_writable() const {
    return writable;
}

bool MemoryRegion::is_executable() const {
    return executable;
}

std::string MemoryRegion::get_pathname() const {
    return pathname;
}
