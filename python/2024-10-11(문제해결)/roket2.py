SIZE = 3

def print_cone():
    for i in range(SIZE *2-1 ):
        print(' ' * (SIZE * 2 - i - 1) + '/' * (i + 1) + '**' + '\\' * (i + 1))

def print_line():
    print('+' + '=*' * (SIZE * 2) + '+')

def print_top_box():
    for i in range(SIZE):
        print('|' + '.' * (SIZE - i - 1) + '/\\' * (i + 1) + '.' * (2 * (SIZE - i - 1)) + '/\\' * (i + 1) + '.' * (SIZE - i - 1) + '|')

def print_bottom_box():
    for i in range(SIZE):
        print('|' + '.' * i + '\\/' * (SIZE - i) + '.' * (2 * i) + '\\/' * (SIZE - i) + '.' * i + '|')

def main():
    print_cone()
    print_line()
    print_top_box()
    print_bottom_box()
    print_line()
    print_bottom_box()
    print_top_box()
    print_line()
    print_cone()

if __name__ == "__main__":
    main()