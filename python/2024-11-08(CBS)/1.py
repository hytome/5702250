def add_commas(number_string):
    reversed_number = number_string[::-1]
    parts = [reversed_number[i:i+3] for i in range(0, len(reversed_number), 3)]
    return ','.join(parts)[::-1]


print(add_commas("12345678"))  