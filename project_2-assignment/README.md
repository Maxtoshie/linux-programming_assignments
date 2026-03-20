---

# Systems Programming: Process Management, I/O, and Multithreading

This repository contains the source code and documentation for Project 2. The project focuses on low-level Linux systems programming, including process lifecycle management, inter-process communication (IPC), performance analysis of system calls, and POSIX multithreading.

## Project Objectives

1.  **Inter-Process Communication:** Implementing a command pipeline using `fork()`, `pipe()`, and `execvp()`.
2.  **Performance Evaluation:** Comparative analysis of low-level system calls versus buffered standard I/O.
3.  **Data Parallelism:** Developing a multithreaded prime number counter with 16 threads and mutex synchronization.
4.  **Concurrent File Processing:** Implementing a multi-threaded keyword search utility with shared file-writing protection.

## Technical Specifications

* **Language:** C (C89/C90 standard)
* **Coding Style:** Betty Style / ALX-Holberton compliant
* **Operating System:** Linux/Unix
* **Tools Used:** `gcc`, `strace`, `pthread`, `gdb`

## Installation and Compilation

To ensure compliance with the project requirements, use the following compilation flags:

```bash
# Question 1: Pipe and Process Communication
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 q1_pipe.c -o q1_pipe

# Question 2: I/O Comparison Utility
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 q2_copy.c -o q2_copy

# Question 3: Multithreaded Prime Counter
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 q3_prime.c -o q3_prime -lpthread

# Question 4: Concurrent Keyword Search
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 q4_search.c -o search -lpthread
```

## Execution Instructions

### Process Pipeline (Question 1)
To execute the pipeline and trace the system call sequence:
```bash
strace -f -e trace=process,pipe,dup2,openat ./q1_pipe
```

### Performance Analysis (Question 2)
Prepare a 100MB test file:
```bash
dd if=/dev/urandom of=largefile.bin bs=1M count=100
```
Analyze system call counts for both versions:
```bash
# Version 1: Low-level read/write
strace -c ./q2_copy 1

# Version 2: Standard I/O (Buffered)
strace -c ./q2_copy 2
```

### Multithreaded Counting (Question 3)
Run the 16-threaded prime number utility:
```bash
./q3_prime
```

### Keyword Search (Question 4)
Run the search utility with the following syntax:
```bash
./search <keyword> <output_file> <input_files...> <number_of_threads>
```

## Analysis Summary

### I/O Performance
The analysis conducted via `strace` demonstrates that Version 2 (Standard I/O) is significantly more efficient than Version 1 (System Calls). This is attributed to the internal buffering mechanism of the C standard library, which minimizes the overhead caused by frequent transitions between User Mode and Kernel Mode.

### Synchronization and Concurrency
In Questions 3 and 4, `pthread_mutex_t` was utilized to maintain data integrity. The implementation avoids race conditions while maximizing throughput by ensuring that critical sections are kept to the minimum necessary length.

---
