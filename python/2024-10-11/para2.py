def print_line(length):
    print('*' * length)

def print_box(width, height):
    for i in range(height):
        if i == 0 or i == height - 1:
            print('*' * width)
        else:
            print('*' + ' ' * (width - 2) + '*')

def main():
    # 각 도형 출력
    print_line(10)
    print()
    print_line(6)
    print()
    print_line(50)
    print()
    print_box(10, 3)
    print()
    print_box(5, 4)

if __name__ == "__main__":
    main()