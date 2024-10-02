def print_design():
    for i in range(1, 10, 2):
        line = '-' * ((11 - i) // 2)
        middle = str(i) * i
        print(line + middle + line)

print_design()