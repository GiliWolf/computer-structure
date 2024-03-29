# 315144907 Gili Wolf
.extern pstring
.extern printf

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

.section .text
.global run_func
.type run_func, @function
# RUN FUNC:
#   args: int choice, Pstring *pstr1, Pstring *pstr2
#   no return value
#   ------------------------------------------------
#   this function calls a specific part of code according to the choice argument recieved.
#   valid options: 31 - call pstrlen of each Pstring to calculate its length, then prints both lengths
#                  33 - use swapCase to swap upper and lower case letters for each Pstring, then prints the two Pstrings
#                  34 - receives from the user two integers as start and end indices. Then, call pstrijcpy with both
#                       Pstring as parameters, and prints the return value and pstr2
#   Register usage:
#       %r13- temporary saves pstr2 in choise33
#       %r14 - temporary saves pstr1 in choise34
#       %r15 - temporary saves pstr2 in choise34

run_func:
    # reset 
    pushq %rbp
    movq %rsp, %rbp

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

    # iff not equal to one of the above - print error
    jmp .print_error



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

.print_error:
    movq $error_msg, %rdi
    xorq %rax, %rax
    call printf
    jmp .exit

.exit:
    # exit program
    xorq %rax, %rax
    movq %rbp, %rsp
    popq %rbp
    ret








