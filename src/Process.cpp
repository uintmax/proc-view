#include "Process.h"

Process::Process(pid_t pid) {
    // Check if directory for given process id exists in procfs
    const std::string proc_path = PROCFS_MOUNT + std::to_string(pid);
    if (!std::filesystem::is_directory(proc_path))
        throw std::runtime_error(proc_path + " does not exist");

    this->pid = pid;

    // Save ownership information of process
    struct stat info{};
    if (stat(proc_path.c_str(), &info) == -1)
        throw std::runtime_error("Could not acquire ownership information of process");

    struct passwd *pw = getpwuid(info.st_uid);
    if (!pw)
        throw std::runtime_error("Could not acquire passwd struct of process");
    this->uid = pw->pw_uid;
}

pid_t Process::get_pid() const {
    return pid;
}

__uid_t Process::get_uid() const {
    return uid;
}
