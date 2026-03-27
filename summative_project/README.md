
***

# ALU Systems Programming Summative Project
**Student:** Maxwel Okoth  
**Environment:** Ubuntu 22.04 LTS (ThinkPad X280)  
**Compiler:** gcc (Ubuntu 11.4.0), nasm (2.15.05)

## Overview
This repository contains the complete implementation of the Systems Programming Summative Project. The project covers low-level binary analysis, x86_64 Assembly, Python-C integration, and advanced multi-threaded synchronization using POSIX threads.

---

## Task 1: Reverse Engineering & ELF Analysis
- **Source File:** `task1_elf.c`
- **Binary:** `program` (Stripped)
- **Compilation:**
  ```bash
  gcc -Wall -O0 -fno-inline -o program task1_elf.c
  strip program
  ```
- **Description:** A C program designed to demonstrate heap/stack allocation and loop structures. 
- **Analysis Execution:**
  - `readelf -h program`: View ELF Header (Entry point, machine type).
  - `objdump -d program`: Disassemble the text section.
  - `strace ./program`: Trace system calls like `mmap` for memory allocation.

---

## Task 2: x86_64 Assembly File Processing
- **Source File:** `task2_temp.asm`
- **Data Input:** `temperature_data.txt`
- **Compilation:**
  ```bash
  nasm -f elf64 task2_temp.asm -o task2_temp.o
  ld task2_temp.o -o task2_temp
  ```
- **Execution:** `./task2_temp`
- **Expected Output:**
  ```text
  Total readings count: [X]
  Valid readings count: [Y]
  ```

---

## Task 3: Python C Extension (Industrial Analytics)
- **Source Files:** `vibration_module.c`, `setup.py`, `test_vibration.py`
- **Compilation:**
  ```bash
  python3 setup.py build_ext --inplace
  ```
- **Execution:** `python3 test_vibration.py`
- **Description:** Integrates high-performance C logic into Python to calculate RMS, peak-to-peak values, and threshold alerts for vibration sensor data.

---

## Task 4: Multi-threaded Baggage Handling System
- **Source File:** `task4_baggage.c`
- **Compilation:**
  ```bash
  gcc -Wall -pthread -o baggage task4_baggage.c
  ```
- **Execution:** `./baggage`
- **Logic:** Implements the **Producer-Consumer pattern**.
  - **Loader (Producer):** Adds luggage to a 5-slot belt using `pthread_cond_signal`.
  - **Aircraft (Consumer):** Removes luggage using `pthread_cond_wait`.
  - **Monitoring Thread:** Reports total loaded and dispatched items every 5 seconds to ensure system integrity.
- **Expected Output:** Real-time logs of luggage movement and periodic status reports from the monitor thread.

---

## Task 5: Digital Library Reservation System (TCP/IP)
- **Source Files:** `server.c`, `client.c`
- **Compilation:**
  ```bash
  gcc -Wall -pthread -o server server.c
  gcc -Wall -o client client.c
  ```
- **Execution:**
  1. Start the central server: `./server`
  2. Start one or more clients: `./client`
- **Protocol:**
  - **Authentication:** Client must provide an ID starting with `ALU`.
  - **Reservation:** Students select books by index (1-3).
  - **Conflict Handling:** The server utilizes `pthread_mutex_t` to lock the library database during a transaction, preventing two students from reserving the same book simultaneously.
- **Expected Output:** "RESERVED_SUCCESS" for the first student and "ALREADY_TAKEN" for subsequent attempts on the same book.

---

## Repository Structure
```text
.
├── task1_elf.c           # ELF analysis source
├── task2_temp.asm        # Assembly source
├── temperature_data.txt  # Input data for Task 2
├── vibration_module.c    # C Extension source
├── setup.py              # Python build script
├── test_vibration.py     # Python test suite
├── task4_baggage.c       # Threaded baggage logic
├── server.c              # Central library server
├── client.c              # Library student client
└── README.md             # This documentation
```

---

### **Final Instruction for Recompilation**
To ensure all updates (including the monitoring thread and library logic) are active:
1. Delete old binaries: `rm -f program task2_temp baggage server client`
2. Run your build commands as listed in each section above.
