
.section .rodata
error_msg: 
    .string "invalid option!\n"
print_char:
    .string "this char: %c\n"

.section .text
.global pstrlen
.type pstrlen, @function
pstrlen:
    # reset 
    pushq %rbp
    movq %rsp, %rbp

    # get length of the pstr
    movzbl (%rdi), %rdi

    # set return value
    movq %rdi, %rax

    
    # exit program
    jmp .exit

.section .text
.global swapCase
.type swapCase, @function
swapCase:
    # reset 
    pushq %rbp
    movq %rsp, %rbp
    # keep pstring pointer in register
    movq %rdi, %r15

    # keep length of string
    movzbl (%r15), %r14

.swap:
    incq %r15
    # Read 1st byte from string
    movb (%r15), %al

    # If we're at the end of the string, exit
    cmpb $0x0, %al
    je .exit2

    # check if lower/upper case:
    cmpb $0x61, %al
    # greater than 61 (is lower case)
    jae .change_to_upper
    # elsee (is upper case)
    jmp .change_to_lower


.change_to_upper:
    subb $0x20,  %al
    movb %al, (%r15)
    jmp .swap

.change_to_lower:
    addb $0x20,  %al
    movb %al, (%r15)
    jmp .swap

.exit2:
    # reset the pointer to the begging of the pstring
    subq %r14, %r15
    decq %r15
    movq %r15, %rax
    # exit program
    movq %rbp, %rsp
    popq %rbp
    ret


.section .text
.global pstrijcpy
.type pstrijcpy, @function
pstrijcpy:
    # reset 
    pushq %rbp
    movq %rsp, %rbp

    # allocate space for args lengths
    subq $32, %rsp

    # save args in register
    movq %rdi, %r8 # pstring1
    movq %rsi, %r9 # pstring2
    movq %rdx, %r10 # i
    movq %rcx, %r11 # j

# VALIDATION-
    # check i <= j:
    cmpq %rdx, %rcx
    jb .print_error # if j below i 

    # check j < pstring1.length
    xorq %r12, %r12
    movb (%rdi), %r12b # pstring1.length
    cmpb %r11b, %r12b
    jbe .print_error

     # check j < pstring2.length
    xorq %r12, %r12
    movb (%rsi), %r12b # pstring2.length
    cmpb %r11b, %r12b
    jbe .print_error

    # keep lengths of strings
    movzbl (%r8), %r13 # length of str1 (dest)
    movzbl (%r9), %r14 # length of str2 (source)
.loop:
    incq %r8
    incq %r9
    # Read 1st byte from source string
    movb (%r9), %al

    # If we're at the end of the string, exit
    cmpb $0x0, %al
    je .exit2
    
    # need to compare i >j ? - meaning we need to stop coping 

    # movb %al, (%r9)

    # increament i

    # exit program
    jmp .exit
    
.print_error:
    movq $error_msg, %rdi
    xorq %rax, %rax
    call printf
    jmp .exit

.exit:
    # exit program
    movq %rbp, %rsp
    popq %rbp
    ret