def decimal_to_binary(decimal):
    if decimal == 0:
        return 0

    binary = 0
    place = 1

    while decimal > 0:
        remainder = decimal % 2
        binary += remainder * place
        decimal //= 2
        place *= 10

    return binary
