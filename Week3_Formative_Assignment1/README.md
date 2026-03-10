# Systems Programming: Formative Assessment 1

This repository contains four projects focused on low-level Linux systems programming, including ELF binary analysis, system call monitoring, Python C-extensions, and Unix signal handling.

## Project Overviews
* **Project 1:** Static analysis of a binary (`data_sync.c`) to determine its functionality.
* **Project 2:** Monitoring file-related system calls using `strace` (`syscall_monitor.c`).
* **Project 3:** Optimizing Python code using a C extension (`fast_math.c`).
* **Project 4:** Handling Unix signals in a background service (`monitor_service.c`).

## Instructions

### Compilation
Compile the C programs using:
- `gcc -Wall -Werror -Wextra -pedantic -std=gnu89 <file>.c -o <name>`

### Running Projects
1. **Project 1:** Inspect using `nm -u` and `objdump -h`.
2. **Project 2:** Run `strace -o output.txt ./syscall_monitor` to capture system calls.
3. **Project 3:** - Build: `python3 setup.py build_ext --inplace`
   - Run: `python3 benchmark.py`
4. **Project 4:** - Run: `./monitor_service`
   - Send signals from a second terminal: `kill -SIGUSR1 <pid>`
