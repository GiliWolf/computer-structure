from random import randint

n = int(input("n >> "))
fname = input("file name >> ")

# with open(fname, "wb") as f:
#     for j in range(n):
#         barr = [randint(0,10).to_bytes(4, byteorder='little')]
#         f.write(b''.join(barr))


def generate_matrix(fname, n):
    with open(fname, "wb") as f:
        for _ in range(n):
            barr = [randint(0, 10).to_bytes(4, byteorder='little') for _ in range(n)]
            f.write(b''.join(barr))

# Example usage:
generate_matrix(fname, n)  # Generates a 3x3 matrix and writes it to "matrix.bin"
