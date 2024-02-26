from random import randint

n = int(input("n >> "))
fname = input("file name >> ")

with open(fname, "wb") as f:
    for j in range(n):
        barr = [randint(0,100).to_bytes(4, byteorder='little')]
        f.write(b''.join(barr))
