# 315144907 Gili Wolf
.section .rodata
error_msg: 
    .string "invalid option!\n"


.section .text
.global pstrlen
.type pstrlen, @function
# PSTRLEN:
#   args: Pstring* pstr
#   return value: char (representing length of Pstring)
#   ------------------------------------------------
#   Given a pointer to a Pstring, the function returns its length by accesing the length field 
#   found in the first byte of pstr
pstrlen:
    # reset 
    pushq %rbp
    movq %rsp, %rbp

    # get length of the pstr
    movzbq (%rdi), %rdi

    # set return value
    movq %rdi, %rax

    # exit program
    jmp .exit

.section .text
.global swapCase
.type swapCase, @function
#   SWAPCASE:
#   args: Pstring *pstr
#   return value: Pstring*
#   ------------------------------------------------
#   Given a pointer to a Pstring, the function turns every capital letter to a little one and vice versa.
#   ALGO: check if letter => 0x61 ?
#               true: check if <= 0x7a ?
#                       true: lower cased, needs to be swapped to upper case
#                       false: not a letter, continue without swapping
#               false: check if <= 0x5a ?
#                       true: check if >= 0x41 ?
#                               true: uppercase, needs to be swapped to lower case
#                               false: not a letter, continue without swapping
#                       false: not a letter, continue without swapping
#   Register usage:
#       %r15 - saves pstr
#       %r14 - saves pstr length
#       %al - temporery saves current char
swapCase:
    # reset 
    pushq %rbp
    movq %rsp, %rbp
    # keep pstring pointer in register
    movq %rdi, %r15

    # keep length of string
    movzbq (%r15), %r14

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

    # iff not both, not a letter, continue without swapping:
    jmp .swap


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

# exit for choice 33
.exit2:
    # reset the pointer to the begging of the pstring
    subq %r14, %r15
    decq %r15
    movq %r15, %rax
    # exit program
    movq %rbp, %rsp
    popq %rbp
    ret

#   PSTRIJCOPY:
#   args: Pstring* dst, Pstring* src, char i, char j
#   return value: Pstring*
#   ------------------------------------------------
#   Given pointers to two Pstrings, and two indices, the function copies src[i:j]
#   into dst[i:j] and returns the pointer to dst. If either i or j are invalid given src and
#   dst sizes, no changes is made to dst, and an error message is printted.
#   Register usage:
#       %r13 - pstring1
#       m%r14 - pstring2
#       %r10 - i
#       %r11 - j
#       %r12 - temporary saves pstr length in order to compare to j
#       %al - temporery saves current char
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
    # print error
    movq $error_msg, %rdi
    xorq %rax, %rax
    call printf
    # return original dest ptr (pstring1)
    movq %r13, %rax
    # reallocate rsp 
    addq $16, %rsp
    jmp .exit

# exit for choice 34
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
# general exit
.exit:
    # exit program
    movq %rbp, %rsp
    popq %rbp
    ret