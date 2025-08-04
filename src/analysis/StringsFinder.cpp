#include "StringsFinder.h"

namespace analysis {
    std::vector<std::string> StringsFinder::find() {
        std::vector<std::string> strings;
        for (const auto &region: proc.get_memory_regions()) {
            // Can not read [vvar] memory region
            if (region.get_pathname() == "[vvar]")
                continue;
            if (region.is_readable() && !region.is_executable()) {
                auto read_addr = region.get_start_addr();
                while (read_addr < region.get_end_addr()) {
                    auto space_left = region.get_end_addr() - read_addr;
                    auto read_size = std::min(buffer_size, space_left);
                    std::vector<uint8_t> buffer(read_size);
                    proc.read(read_addr, buffer);

                    // Maybe change data type -> size
                    for (uint32_t i = 0; i < buffer.size(); i++) {
                        auto check_len = std::min(max_len, i);
                        if (buffer[i] == 0) {
                            // No need to check i for null again
                            for (int char_counter = 1; char_counter <= check_len; char_counter++) {
                                if (buffer[i - char_counter] == 0 || !std::isprint(buffer[i - char_counter])) {
                                    if (char_counter >= min_len) {
                                        strings.emplace_back(reinterpret_cast<char *>(&buffer[i - char_counter + 1]));
                                    }
                                    break;
                                }
                            }
                        }

                        read_addr += read_size;
                    }
                }
            }
        }
        return strings;
    }
}
