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

    /**
     * Returns the process id
     */
    pid_t get_pid() const;

    /**
     * Returns the user id
     */
    __uid_t get_uid() const;

private:
    static constexpr std::string PROCFS_MOUNT = "/proc/";
    pid_t pid;
    __uid_t uid;
};


#endif //PROCESS_H
