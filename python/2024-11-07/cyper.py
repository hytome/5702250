def caesar_cipher(message, shift):
    encrypted_message = ""
    for char in message:
        if char.isalpha():
            shift_amount = shift % 26
            if char.islower():
                start = ord('a')
            else:
                start = ord('A')
            encrypted_char = chr(start + (ord(char) - start + shift_amount) % 26)
            encrypted_message += encrypted_char
        else:
            encrypted_message += char
    return encrypted_message


secret_message = input("Your secret message: ")
secret_key = int(input("Your secret key: "))


encoded_message = caesar_cipher(secret_message, secret_key)
print("The encoded message:", encoded_message)