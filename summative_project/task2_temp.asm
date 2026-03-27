section .data
    file_name db "temperature_data.txt", 0
    total_lbl db "Total readings: ", 0
    valid_lbl db "Valid readings: ", 0
    newline   db 10
    
section .bss
    fd         resq 1
    buffer     resb 4096
    total_cnt  resq 1
    valid_cnt  resq 1
    num_str    resb 20

section .text
    global _start

_start:
    ; Open file [cite: 138, 152]
    mov rax, 2          ; sys_open
    mov rdi, file_name
    mov rsi, 0          ; O_RDONLY
    syscall
    cmp rax, 0
    jl exit_error       ; Error handling for file opening [cite: 150]
    mov [fd], rax

    ; Read file into memory [cite: 138]
    mov rdi, [fd]
    mov rax, 0          ; sys_read
    mov rsi, buffer
    mov rdx, 4096
    syscall
    mov r12, rax        ; Store bytes read in r12

    ; Traverse and count [cite: 139, 153]
    xor r13, r13        ; index
    xor r14, r14        ; total lines
    xor r15, r15        ; valid lines
    mov rbx, 1          ; Flag: is current line non-empty? (Assume empty=0)
    xor rbx, rbx

.loop:
    cmp r13, r12
    jge .done
    
    mov al, [buffer + r13]
    
    cmp al, 10          ; Check for \n 
    je .handle_newline
    cmp al, 13          ; Skip \r 
    je .skip_char
    
    mov rbx, 1          ; Line has content
.skip_char:
    inc r13
    jmp .loop

.handle_newline:
    inc r14             ; Increment Total [cite: 143]
    add r15, rbx        ; Increment Valid if rbx was 1 [cite: 144]
    xor rbx, rbx        ; Reset for next line
    inc r13
    jmp .loop

.done:
    ; Final line check (if file doesn't end in newline)
    cmp rbx, 1
    jne .print_results
    inc r14
    inc r15

.print_results:
    ; Print Total readings [cite: 145, 146]
    mov rax, 1
    mov rdi, 1
    mov rsi, total_lbl
    mov rdx, 16
    syscall
    
    mov rax, r14
    call print_number
    
    ; Print Valid readings [cite: 145, 147]
    mov rax, 1
    mov rdi, 1
    mov rsi, valid_lbl
    mov rdx, 16
    syscall
    
    mov rax, r15
    call print_number

    ; Close and exit
    mov rax, 3
    mov rdi, [fd]
    syscall

exit_error:
    mov rax, 60
    xor rdi, rdi
    syscall

; Simple helper to print integers
print_number:
    mov rcx, num_str
    add rcx, 19
    mov byte [rcx], 10
    mov rbx, 10
.num_loop:
    xor rdx, rdx
    div rbx
    add dl, '0'
    dec rcx
    mov [rcx], dl
    test rax, rax
    jnz .num_loop
    
    mov rax, 1
    mov rdi, 1
    mov rsi, rcx
    mov rdx, num_str
    add rdx, 20
    sub rdx, rcx
    syscall
    ret
