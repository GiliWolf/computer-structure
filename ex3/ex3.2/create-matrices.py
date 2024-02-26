from random import randint

n = int(input("n >> "))
fname = input("file name >> ")

with open(fname, "wb") as f:
    for j in range(n):
        barr = [int(1).to_bytes(4, byteorder='little') for i in range(n)]
        f.write(b''.join(barr))

