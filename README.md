# proc-view

Process analysis tool for Linux.

I work on this project to learn more about Linux and modern C++.  
I am always open to suggestions, feel free to create a GitHub issue.

## Features

- List information about running processes
- Find null-terminated strings in process memory
- Memory scanner
- Memory editor
- Lua scripting API for custom user scripts

### TODO

- Detection of runtime patches in executable sections
    - Info about suspected hooks -> e.g. follow jmp
- Disassemble machine code at specified address
- Entropy calculation
- Debugging functionality
- eBPF program for process observation in kernel mode
- Add GTest 

## Build

`cmake --preset release`

`cmake --build build-relase`

## Dependencies

All dependencies besides Qt will be automatically installed via vcpkg.

- sol2
- Lua
- Qt6 (Set `QT_ROOT` environment variable to your installation directory)

## References

- [procfs man page](https://man.archlinux.org/man/procfs.5.en)
- [procfs maps man page](https://man.archlinux.org/man/proc_pid_maps.5.en)
- [pfs by dtrugman](https://github.com/dtrugman/pfs)
- [Yama security module](https://www.kernel.org/doc/Documentation/security/Yama.txt)
