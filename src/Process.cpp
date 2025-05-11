#include "Process.h"

Process::Process(pid_t pid) {
    // Check if directory for given process id exists in procfs
    const std::string proc_path = PROCFS_MOUNT + std::to_string(pid);
    if (!std::filesystem::is_directory(proc_path))
        throw std::runtime_error(proc_path + " does not exist");

    this->pid = pid;

    // Save ownership information of process
    // TODO: Read from procfs status file instead -> Contains more information
    struct stat info{};
    if (stat(proc_path.c_str(), &info) == -1)
        throw std::runtime_error("Could not acquire ownership information of process");

    struct passwd *pw = getpwuid(info.st_uid);
    if (!pw)
        throw std::runtime_error("Could not acquire passwd struct of process");
    this->uid = pw->pw_uid;
}

std::vector<Process> Process::get_all_processes() {
    std::vector<Process> proc_list;

    // Iterate over procfs directory
    for (const auto &entry: std::filesystem::directory_iterator(PROCFS_MOUNT)) {
        // Each process is represented by a directory in the procfs
        if (!entry.is_directory())
            continue;

        // Process directories only contain digits -> pid
        std::string dir_name = entry.path().filename().string();
        if (!std::ranges::all_of(dir_name, isdigit))
            continue;

        pid_t pid = std::stoi(dir_name);
        Process proc(pid);
        proc_list.push_back(proc);
    }

    return proc_list;
}

pid_t Process::get_pid() const {
    return pid;
}

__uid_t Process::get_uid() const {
    return uid;
}

std::filesystem::path Process::get_exe() const {
    std::string exe_path = PROCFS_MOUNT + std::to_string(this->pid) + PROCFS_EXE;
    return std::filesystem::read_symlink(exe_path);
}
