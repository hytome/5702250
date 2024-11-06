def convert_to_alt_caps(s):
    result = ""
    index = 0  
    for char in s:
        if char.isalpha():  
            if index % 2 == 0:
                result += char.lower()  
            else:
                result += char.upper()  
            index += 1
        else:
            result += char  
    return result


print(convert_to_alt_caps("Pikachu"))  
