
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
    # elsee - lower than 61 (is upper case)
    # need to check if lower or equal than 0x5a (Z)
    cmpb $0x5A, %al
    jbe .change_to_lower


.change_to_upper:
    # iff above 0x7A, not a letter - continue without swapping
    cmpb $0x7A, %al
    ja .swap

    # iff not - between the range: [0x61, 0x7a] (lowercase letter)
    subb $0x20,  %al
    movb %al, (%r15)
    jmp .swap

.change_to_lower:
    # iff below 0x41 (A), not a letter - continue without swapping
    cmpb $0x41, %al
    jb .swap 

    # iff not - between the range: [0x41, 0x5a] (uppercase letter)
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

    # allocate space for saving i + j
    subq $16, %rsp

    # save args in register
    movq %rdi, %r13 # pstring1
    movq %rsi, %r14 # pstring2
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

    # keep i+j on stack
    movq %r10, -8(%rbp) # i (-24)
    movq %r11, -16(%rbp) # j (-32)

    # change ptr to string to ptr + i
    addq -8(%rbp), %r13
    addq -8(%rbp), %r14
.loop:
    # in first loop: +1 beacuse of the length in the start of the pointer
    incq %r13 # str1 (dest)
    incq %r14 # str2 (source)

    # get source [i]
    movb (%r14), %al

    # If we're at the end of the string, exit
    cmpb $0x0, %al
    je .exit3
    
    # need to compare i >j ? - meaning we need to stop coping
    movq -8(%rbp), %r12 # get i
    cmpq %r12, -16(%rbp) # compare to j
    jb .exit3

    # dest[i] <- source [i]
    movb %al, (%r13)

    # increament i 
    incq -8(%rbp)

    # continue loop
    jmp .loop

.print_error:
    movq $error_msg, %rdi
    xorq %rax, %rax
    call printf
    jmp .exit

.exit3:
    # reset the pointer to the begging of the pstring
    subq -8(%rbp), %r13
    decq %r13
    movq %r13, %rax
    # reallocate rsp 
    addq $16, %rsp 
    # exit program
    movq %rbp, %rsp
    popq %rbp
    ret

.exit:
    movq %r13, %rax
    # reallocate rsp 
    addq $16, %rsp
    # exit program
    movq %rbp, %rsp
    popq %rbp
    ret