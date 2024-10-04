def main():
    size = 4
    top_half(size)
    bottom_half(size)

def top_half(size):
    for i in range(1, size + 1):
        print("|" + " " * (size - i) + "<>" + "." * (2 * (i - 1)) + "<>" + " " * (size - i) + "|")

def bottom_half(size):
    for i in range(size, 0, -1):
        print("|" + " " * (size - i) + "<>" + "." * (2 * (i - 1)) + "<>" + " " * (size - i) + "|")

main()