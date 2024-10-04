def main():
    line()
    top_half()
    bottom_half()
    line()

def line():
    print("#" + "=" * 16 + "#")

def top_half():
    for i in range(4):
        print("|" + " " * (3 - i) + "<>" + "." * (2 * i) + "<>" + " " * (3 - i) + "|")

def bottom_half():
    for i in range(3, -1, -1):
        print("|" + " " * (3 - i) + "<>" + "." * (2 * i) + "<>" + " " * (3 - i) + "|")

main()