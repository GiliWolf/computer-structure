.extern pstring
.extern printf

.section .data
choise:
    .space 8, 0x0
pstring_1:
    .space 255, 0x0
pstring_2:
    .space 255, 0x0

.section .rodata
see_args:
    .string "choice: %d, str1: %s, str2: %s, len2: %d"
str_len:
    .string "len: %d"
choice_31_output:
    .string "first pstring length: %d, second pstring length: %d\n"
choise_33_output:
    .string "length: %d, string: %s\n"
choise_34_output:
    .string "length: %d, string: %s\n"
error_msg: 
    .string "invalid option!\n"
scanf_char_format:
    .string "%hhu %hhu"
check_i_j:
    .string "i: %hhu, j: %hhu\n"

.section .text
.global run_func
.type run_func, @function
run_func:
    # reset 
    pushq %rbp
    movq %rsp, %rbp
    
    # as 1st arg is 31
    # movq $0x1F, %rdi
    # get choise 

    # 31:
    movq $0x1F, %rcx
    cmp %rdi, %rcx
    je .choise31

    # 33:
    movq $0x21, %rcx
    cmp %rdi, %rcx
    je .choise33

    # 34:
    movq $0x22, %rcx
    cmp %rdi, %rcx
    je .choise34



.choise31:
    # allocate space for both lengths
    subq $16, %rsp

    # set pstring2 as 1st argumnet and calls the function
    movq %rdx, %rdi
    call pstrlen
    # pushes the result to the stack:
    movq %rax, -8(%rbp)

    # set pstring1 as 1st argumnet and calls the function
    movq %rsi, %rdi
    call pstrlen
    # pushes the result to the stack:
    movq %rax, -16(%rbp)
 
    # print lengths of the strings
    movq $choice_31_output, %rdi
    movq -16(%rbp), %rsi
    movq -8(%rbp), %rdx
    xorq %rax, %rax
    call printf

    # reallocate rsp 
    addq $16, %rsp 

    # exit programm
    jmp .exit

.choise33:
    # save second string in temp register
    movq %rdx, %r13 

    # set pstring1 as 1st argumnet and calls the function
    movq %rsi, %rdi
    call swapCase
    
    # print 1st pstring length and string 
    movq $choise_33_output, %rdi
    movzb (%rax), %rsi
    incq %rax
    movq %rax, %rdx
    xorq %rax, %rax
    call printf

    # set pstring2 as 1st argumnet and calls the function
    movq %r13, %rdi
    call swapCase

    # print 2nd pstring length and string 
    movq $choise_33_output, %rdi
    movzb (%rax), %rsi
    incq %rax
    movq %rax, %rdx
    xorq %rax, %rax
    call printf


    # exit programm
    jmp .exit

.choise34:
    # allocate space for both lengths
    subq $16, %rsp
    
    # save temporary pstring pointers:
    movq %rsi, %r14 # str1
    movq %rdx, %r15 # str 2

    # erase:
    movq $0x0, -8(%rbp)
    movq $0x0, -16(%rbp)
    xorq %rsi, %rsi
    xorq %rdx, %rdx

    # scan i + j
    movq $scanf_char_format, %rdi
    leaq -8(%rbp), %rsi
    leaq -16(%rbp), %rdx
    xorq %rax, %rax
    call scanf

    # check i, j
    movq $check_i_j, %rdi
    movq -8(%rbp), %rsi
    movq -16(%rbp), %rdx
    xorq %rax, %rax
    call printf

    # set args and call pstrijcpy
    movq %r14, %rdi
    movq %r15, %rsi
    movq -8(%rbp), %rdx
    movq -16(%rbp), %rcx
    call pstrijcpy
    
    # print alternated pstring1 from function
    movq $choise_34_output, %rdi
    movzb (%rax), %rsi
    incq %rax
    movq %rax, %rdx
    xorq %rax, %rax
    call printf

    # print pstring2 from function
    movq $choise_34_output, %rdi
    movzb (%r15), %rsi
    incq %r15
    movq %r15, %rdx
    xorq %rax, %rax
    call printf

    # reallocate rsp 
    addq $16, %rsp 
    jmp .exit

.exit:
    # exit program
    xorq %rax, %rax
    movq %rbp, %rsp
    popq %rbp
    ret








