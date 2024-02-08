# 315144907 Gili Wolf

.extern printf
.extern scanf
.extern srand
.extern rand

.section .data
user_seed:
    .space 8, 0x0
rand_number:
    .space 8, 0x0
rand_mod_10:
    .space 8, 0x0
user_guess:
    .space 8, 0x0
counter:
    .space 8, 0x0
max_tries:
    .space 8, 0x0

.section .rodata
user_seed_req:
    .string "Enter configuration seed: "
scanf_format:
    .string "%d"
rand_msg:
    .string "random number: %d"
guess_msg:
    .string "What is your guess? "
incorrect_msg:
    .string "Incorrect.\n"
lose_msg:
    .string "Game over, you lost :(. The correct answer was %d\n"
win_msg:
    .string "Congratz! You won!\n"

.section .text
.global main
.type main, @function
# GUESSING GAME:
#   ------------------------------------------------
#   1) asks user to enter a configuration value - the seed for the rand() function
#   2) generates a random number between 0 and N. 
#   3) prints “What is your guess?” and scan number from user. 
#   4) If the guess is incorrect, the program prints “Incorrect.”
#   5) stops when either M iterations of the game are passed, or the user guesses the number correctly.
#   global values: 
#   N = 10 and M = 5.
main:
    # reset 
    pushq %rbp
    movq %rsp, %rbp

    # print welcome massage: 
    movq $user_seed_req, %rdi
    xorq %rax, %rax
    call printf

    # scan seed number from user
    movq $scanf_format, %rdi
    movq $user_seed, %rsi
    xorq %rax, %rax
    call scanf

   # set the seed
    movq user_seed, %rdi
    xorq %rax, %rax
    call srand

    # get random number
    xorq %rax, %rax
    call rand

    # get random number fromthe return register - rax
    movq %rax, rand_number

    # compute rand_number mod 10
    movq rand_number, %rax # set low-order bits
    movq $0x0, %rdx # reset high-order bits
    movq $0xA, %rbx  # set divisor to 10
    divq %rbx       # divide rdx:rax by 10
    movq %rdx, rand_mod_10 # get remainder (mod10) from rdx

    # reset index counter (i) and maximum tries (m)
    movq $0x0, %rcx
    movq %rcx, counter
    movq $0x5, %r9
    movq %r9, max_tries


.loop:
    # get counter and max tries
    movq counter, %rcx
    movq max_tries, %r9

    # jump to lose if counter >= max tries, and increament the counter
    cmpq %rcx, %r9
    jle .lose
    incq %rcx
    movq %rcx, counter

    # print: "what is your guess?"
    movq $guess_msg, %rdi
    xorq %rax, %rax
    call printf

    # scan for guess
    movq $scanf_format, %rdi
    movq $user_guess, %rsi
    xorq %rax, %rax
    call scanf

    # access the user guess
    movq user_guess, %r8

    # compare user guess with random number. if equal jump to 'win'
    cmpq %r8, rand_mod_10
    je .win

    # print "incorrect"
    movq $incorrect_msg, %rdi
    xorq %rax, %rax
    call printf

    # return to the loop
    jmp .loop


.win:
    # print winning message and jump to exit
    movq $win_msg, %rdi
    xorq %rax, %rax
    call printf
    jmp .exit

.lose:
    # print losing message and jump to exit
    movq $lose_msg, %rdi
    movq rand_mod_10, %rsi
    xorq %rax, %rax
    call printf

.exit:
    # exit program
    xorq %rax, %rax
    movq %rbp, %rsp
    popq %rbp
    ret
