def print_cone(size):
    for i in range(size * 2 - 1):
        print(' ' * (size * 2 - i - 1) + '/' * (i + 1) + '**' + '\\' * (i + 1))

def print_line(size):
    print('+' + '=*' * (size * 2) + '+')

def print_top_box(size):
    for i in range(size):
        print('|' + '.' * (size - i - 1) + '/\\' * (i + 1) + '.' * (2 * (size - i - 1)) + '/\\' * (i + 1) + '.' * (size - i - 1) + '|')

def print_bottom_box(size):
    for i in range(size):
        print('|' + '.' * i + '\\/' * (size - i) + '.' * (2 * i) + '\\/' * (size - i) + '.' * i + '|')

def main():
    try:
        size = int(input("Enter the size of the rocket: "))
    except EOFError:
        size = 3  # 기본값 설정
    print_cone(size)
    print_line(size)
    print_top_box(size)
    print_bottom_box(size)
    print_line(size)
    print_bottom_box(size)
    print_top_box(size)
    print_line(size)
    print_cone(size)

if __name__ == "__main__":
    main()