def main():
    size = 4
    line(size)
    top_half(size)
    bottom_half(size)
    line(size)

def line(size):
    print("#" + "=" * (2 * size + 2) + "#")

def top_half(size):
    for line in range(1, size + 1):
        print("|", end="")
        for space in range(1, (line * -2 + (2 * size)) + 1):
            print(" ", end="")
        print("<>", end="")
        for dot in range(1, (line * 4 - 4) + 1):
            print(".", end="")
        print("<>", end="")
        for space in range(1, (line * -2 + (2 * size)) + 1):
            print(" ", end="")
        print("|")

def bottom_half(size):
    for line in range(size, 0, -1):
        print("|", end="")
        for space in range(1, (line * -2 + (2 * size)) + 1):
            print(" ", end="")
        print("<>", end="")
        for dot in range(1, (line * 4 - 4) + 1):
            print(".", end="")
        print("<>", end="")
        for space in range(1, (line * -2 + (2 * size)) + 1):
            print(" ", end="")
        print("|")

main()