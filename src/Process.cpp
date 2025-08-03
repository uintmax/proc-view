#include "Process.h"

Process::Process(pid_t pid) {
    // Check if directory for given process id exists in procfs
    const std::string proc_path = procfs_mount + std::to_string(pid);
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

    auto cmdline_path = proc_path + procfs_cmdline;
    std::ifstream cmdline_stream(cmdline_path);
    std::stringstream cmdline_buffer;
    cmdline_buffer << cmdline_stream.rdbuf();
    this->cmdline = cmdline_buffer.str();

    auto comm_path = proc_path + procfs_comm;
    std::ifstream comm_stream(comm_path);
    std::stringstream comm_buffer;
    comm_buffer << comm_stream.rdbuf();
    this->comm = comm_buffer.str();
    this->comm.pop_back(); // Remove newline
}

std::vector<Process> Process::get_all_processes() {
    std::vector<Process> proc_list;

    // Iterate over procfs directory
    for (const auto &entry: std::filesystem::directory_iterator(procfs_mount)) {
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

std::vector<Process> Process::get_processes_by_name(const std::string &proc_name) {
    auto procs = Process::get_all_processes();
    std::erase_if(procs, [proc_name](const Process &p) {
        return !p.get_comm().starts_with(proc_name);
    });
    return procs;
}

Process Process::get_process_by_name(const std::string &proc_name) {
    auto procs = Process::get_processes_by_name(proc_name);
    if (procs.empty())
        throw std::runtime_error("Process name not found");
    if (procs.size() > 1)
        throw std::runtime_error("Found " + std::to_string(procs.size()) + " processes");

    return procs.front();
}


pid_t Process::get_pid() const {
    return pid;
}

uid_t Process::get_uid() const {
    return uid;
}

std::filesystem::path Process::get_exe() const {
    std::string exe_path = procfs_mount + std::to_string(pid) + procfs_exe;
    return std::filesystem::read_symlink(exe_path);
}

std::string Process::get_cmdline() const {
    return cmdline;
}

std::string Process::get_comm() const {
    return comm;
}

std::vector<MemoryRegion> Process::get_memory_regions() {
    auto maps_path = procfs_mount + std::to_string(pid) + procfs_maps;
    std::ifstream maps_stream(maps_path);
    std::stringstream maps_buffer;
    maps_buffer << maps_stream.rdbuf();
    auto maps = maps_buffer.str();

    std::vector<MemoryRegion> memory_regions;

    auto map_entries = maps | std::views::split('\n') | std::ranges::to<std::vector<std::string> >();
    map_entries.pop_back();
    for (const auto &entry: map_entries) {
        memory_regions.push_back(MemoryRegion{entry});
    }

    return memory_regions;
}
