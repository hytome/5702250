def main():
    size = 3
    line(size)
    top_half(size)
    bottom_half(size)
    line(size)

def line(size):
    # `=`의 개수를 조정하여 도형의 너비에 맞춥니다.
    print("#" + "=" * (2 * size + 8) + "#")

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