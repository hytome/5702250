def print_design():
    for i in range(1, 10, 2):
        line = '-' * ((9 - i) // 2)
        print(line + str(i) * i + line)

print_design()