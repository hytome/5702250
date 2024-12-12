def show_twos(n):
    result = f"{n} ="
    while n % 2 == 0:
        result += " 2 *"
        n //= 2
    result += f" {n}"
    print(result)

show_twos(7)
show_twos(18)
show_twos(68)
show_twos(120)
