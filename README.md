# proc-view

Process analysis tool for Linux.

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
