#ifndef PROCESS_H
#define PROCESS_H
#include <sys/types.h>
#include <filesystem>
#include <string>
#include <stdexcept>
#include <sys/stat.h>
#include <pwd.h>
#include <vector>
#include <algorithm>
#include <sys/uio.h>
#include <fstream>
#include <sstream>
#include "MemoryRegion.h"

/**
 * Process class to interact with processes on Linux
 */
class Process {
public:
    /**
     * Constructor for a single process in the procfs
     * Throws a std::runtime_error when the process id does not exist
     */
    Process(pid_t pid);

    /**
     * Returns a list of all processes from procfs
     */
    static std::vector<Process> get_all_processes();

    static std::vector<Process> get_processes_by_name(const std::string &proc_name);

    static Process get_process_by_name(const std::string &proc_name);

    /**
     * Returns the process id
     */
    pid_t get_pid() const;

    /**
     * Returns the user id
     */
    uid_t get_uid() const;

    std::filesystem::path get_exe() const;

    std::string get_cmdline() const;

    std::string get_comm() const;

    std::vector<MemoryRegion> get_memory_regions();


    template<typename T>
    T read(uintptr_t address) {
        T buffer;
        const auto len = sizeof(buffer);
        struct iovec local;
        local.iov_base = &buffer;
        local.iov_len = len;

        struct iovec remote;
        remote.iov_base = reinterpret_cast<void *>(address);
        remote.iov_len = len;

        auto bytes_read = process_vm_readv(this->pid, &local, 1, &remote, 1, 0);
        if (bytes_read == -1) {
            throw std::runtime_error("Could not read from address");
        } else if (bytes_read != len) {
            throw std::runtime_error(
                "Could only read " + std::to_string(bytes_read) + " out of " + std::to_string(len) + " bytes");
        }

        return buffer;
    }

private:
    inline static const std::string procfs_mount = "/proc/";
    inline static const std::string procfs_exe = "/exe";
    inline static const std::string procfs_cmdline = "/cmdline";
    inline static const std::string procfs_comm = "/comm";
    inline static const std::string procfs_maps = "/maps";
    pid_t pid;
    uid_t uid;
    std::string cmdline;
    std::string comm;
};


#endif //PROCESS_H
