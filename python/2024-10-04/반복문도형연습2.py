def main():
    size = 4
    line(size)
    top_half(size)
    bottom_half(size)
    line(size)

def line(size):
    print("#" + "=" * (2 * size + 2) + "#")

def top_half(size):
    for i in range(size):
        print("|" + " " * (size - 1 - i) + "<>" + "." * (2 * i) + "<>" + " " * (size - 1 - i) + "|")

def bottom_half(size):
    for i in range(size - 1, -1, -1):
        print("|" + " " * (size - 1 - i) + "<>" + "." * (2 * i) + "<>" + " " * (size - 1 - i) + "|")

main()