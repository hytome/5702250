def main():
    size = 4
    line(size)
    top_half(size)
    bottom_half(size)
    line(size)

def line(size):
    print("#" + "=" * (2 * size + 8) + "#")

def top_half(size):
    for line in range(1, size + 1):
        spaces = 2 * line - 2
        dots = -4 * line + size * 4
        print("|" + " " * spaces + "<>" + "." * dots + "<>" + " " * spaces + "|")

def bottom_half(size):
    for line in range(size, 0, -1):
        spaces = 2 * line - 2
        dots = -4 * line + size * 4
        print("|" + " " * spaces + "<>" + "." * dots + "<>" + " " * spaces + "|")

main()