#ifndef PROCESS_H
#define PROCESS_H
#include <sys/types.h>
#include <filesystem>
#include <string>
#include <stdexcept>
#include <sys/stat.h>
#include <pwd.h>


class Process {
public:
    Process(pid_t pid);

    pid_t get_pid() const;

    __uid_t get_uid() const;

private:
    static constexpr std::string PROCFS_MOUNT = "/proc/";
    pid_t pid;
    __uid_t uid;
};


#endif //PROCESS_H
