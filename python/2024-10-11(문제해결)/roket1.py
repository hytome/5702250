def print_cone():
    for i in range(5):
        print(' ' * (-1 * i + 5) + "/" * (i + 1) + "**" + "\\" * (i + 1))

def print_line():
    print("+" + "=*" * 6 + "+")



def print_top_box():
    for i in range(3):
         print('|' + '.' * (2 - i) + '/\\' * (i + 1) + '.' * (2 * (2 - i)) + '/\\' * (i + 1) + '.' * (2 - i) + '|')


def print_top_bottom_box():
    for i in range(3):  
        print('|' + '.' * i + '\/' * (3 - i) + '.' * (i * 2) + '\/' * (3 - i) + '.' * i + '|')

def main():
    print_cone()
    print_line()
    print_top_box()
    print_top_bottom_box()
    print_line()
    print_top_bottom_box()
    print_top_box()
    print_line()
    print_cone()

if __name__ == "__main__":
    main()