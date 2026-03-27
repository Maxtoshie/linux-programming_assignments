---

### **README.md Template**

```markdown
# ALU Systems Programming Summative Project
**Student:** Maxwel Okoth  
**Environment:** Ubuntu (ThinkPad X280)

## Overview
This repository contains a suite of systems programming tasks ranging from ELF analysis and x86 Assembly to Python C Extensions and Multi-threaded Network Servers.

---

## Task 1: ELF Reverse Engineering
- **File:** `task1_elf.c`
- **Compilation:** `gcc -Wall -O0 -fno-inline -o program task1_elf.c && strip program`
- **Execution:** `./program`
- **Goal:** Analyze binary structure using `readelf`, `objdump`, and `strace`.

## Task 2: x86 Assembly File Processing
- **Files:** `task2_temp.asm`, `temperature_data.txt`
- **Compilation:** ```bash
  nasm -f elf64 task2_temp.asm -o task2_temp.o
  ld task2_temp.o -o task2_temp
  ```
- **Execution:** `./task2_temp`
- **Input:** A text file containing temperature readings.
- **Output:** Total readings count and non-empty (valid) readings count.

## Task 3: Python C Extension
- **Files:** `vibration_module.c`, `setup.py`, `test_vibration.py`
- **Compilation:** `python3 setup.py build_ext --inplace`
- **Execution:** `python3 test_vibration.py`
- **Expected Output:** Statistical summary (min, max, mean) of vibration data calculated via C logic.

## Task 4: Producer-Consumer (Baggage Handling)
- **File:** `task4_baggage.c`
- **Compilation:** `gcc -Wall -pthread -o baggage task4_baggage.c`
- **Execution:** `./baggage`
- **Description:** Uses `pthread_mutex` and `pthread_cond_t` to synchronize a loader and an aircraft dispatch system.

## Task 5: Digital Library (TCP Sockets)
- **Files:** `server.c`, `client.c`
- **Compilation:**
  ```bash
  gcc -Wall -pthread -o server server.c
  gcc -Wall -o client client.c
  ```
- **Execution:**
  1. Start server: `./server`
  2. Run client: `./client`
- **Validation:** Enter an ID starting with `ALU` e.g ALU-1234 to receive "Access Granted."
```

---
